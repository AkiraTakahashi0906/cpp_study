#include "db_status_sqlserver.h"

vector<DbTableDataCountEntity> db_status_sqlserver::getTableDataCount()
{
    string sql = "\
    SELECT\
        DB_NAME() AS DbName,\
        SCHEMA_NAME(so.schema_id) AS SchemaName,\
        so.name,\
        dps.*,\
        dps.reserved_page_count * 8.0 AS reserved_page_count_kb\
    FROM\
        sys.dm_db_partition_stats dps\
    INNER JOIN\
        sys.objects so\
    ON\
        so.object_id = dps.object_id\
    AND\
    SCHEMA_NAME(so.schema_id) < > 'sys'\
    WHERE index_id IN(0, 1)\
    ORDER BY so.name\
    OPTION(RECOMPILE)\
";
    vector<SqlParameter> parameters;

    std::unique_ptr<SqlserverHelper> helper(new SqlserverHelper);
    nanodbc::result results;
    results = helper->Query(sql, parameters);
    vector<DbTableDataCountEntity> list;
    while (results.next())
    {
        list.push_back(DbTableDataCountEntity(results.get<string>("DbName"),
                                                                    results.get<string>("name"),
                                                                    results.get<int>("row_count"),
                                                                    results.get<double>("reserved_page_count_kb")));
    }

    return list;
}

vector<DbBackupLogEntity> db_status_sqlserver::GetDbBackupLogAll()
{
    string sql = "\
    SELECT\
        name,\
        create_date,\
        recovery_model,\
        recovery_model_desc,\
        isnull(D,'1900/1/1') AS full_backup_finish_date,\
        I AS diff_backup_finish_date,\
        L AS log_backup_finish_date\
        FROM\
        (\
            SELECT\
            d.database_id,\
            d.name,\
            d.create_date,\
            d.recovery_model,\
            d.recovery_model_desc,\
            backup_tbl.type,\
            backup_tbl.backup_finish_date\
            FROM\
            sys.databases AS d\
            LEFT JOIN\
            (SELECT\
                database_name,\
                type,\
                MAX(backup_finish_date) AS backup_finish_date\
                FROM\
                msdb.dbo.backupset\
                GROUP BY\
                database_name,\
                type\
            ) AS backup_tbl\
            ON\
            d.name = backup_tbl.database_name\
        ) AS T\
        PIVOT\
        (\
            MAX(backup_finish_date)\
            FOR type IN(D, I, L)\
        )AS PVT\
        ORDER BY\
        database_id ASC\
        ; ";

    vector<SqlParameter> parameters;

    std::unique_ptr<SqlserverHelper> helper(new SqlserverHelper);
    nanodbc::result results;
    results = helper->Query(sql, parameters);
    vector<DbBackupLogEntity> list;
    while (results.next())
    {
        nanodbc::timestamp timestamp = results.get<nanodbc::timestamp>("create_date");
        nanodbc::timestamp full_backup_finish_date_timestamp = results.get<nanodbc::timestamp>("full_backup_finish_date");
        list.push_back(DbBackupLogEntity(results.get<string>("name"),
                                                            TimeHelper::ToGregorianDate(timestamp),
                                                            TimeHelper::ToGregorianDate(full_backup_finish_date_timestamp)));
    }
    return list;
}

vector<db_status_entity> db_status_sqlserver::GetDbStatus() {

    nanodbc::result results;
    //string sql = "\
    //SELECT\
    //    [test_int],\
    //    [test_string],\
    //    [test_bool],\
    //    [test_datetime],\
    //    [test_float],\
    //    [test_datetime2]\
    //FROM\
    //    [KGWS].[dbo].[test_table]\
    //WHERE\
    //    [test_int] = ?\
    //AND\
    //    [test_string] = ?\
    //AND\
    //    [test_bool] = ?\
    //AND\
    //    [test_datetime] = ?\
    //AND\
    //    [test_float] = ?\
    //AND\
    //    [test_datetime2] = ?\
    //;";

    string sql = "\
    SELECT\
        [test_int],\
        [test_string],\
        [test_bool],\
        [test_datetime],\
        [test_float],\
        [test_datetime2]\
    FROM\
        [KGWS].[dbo].[test_table]\
    WHERE\
        [test_int] = ?\
    ;";

    vector<SqlParameter> parameters;
    const int A = 1;
    parameters.push_back(SqlParameter{ 0,A});

    //const string C = "b";
    //parameters.push_back(SqlParameter{ 1,C});

    //const bool B = true;
    //parameters.push_back(SqlParameter{ 2,B});

    //const boost::gregorian::date boost_date(2021,1,1);
    //parameters.push_back(SqlParameter{ 3,boost_date});

    //const double E = 0.1;
    //parameters.push_back(SqlParameter{ 4,E});

    //const boost::gregorian::date boost_date2(2021, 1, 1);
    //boost::posix_time::time_duration td1(boost::posix_time::hours(12) + boost::posix_time::minutes(12) + boost::posix_time::seconds(12));
    //boost::posix_time::ptime ptime(boost_date2, td1);
    //parameters.push_back(SqlParameter{ 5,ptime });

    std::unique_ptr<SqlserverHelper> helper(new SqlserverHelper);

    results = helper->Query(sql, parameters);
    vector<db_status_entity> list;
    while (results.next())
    {
        nanodbc::timestamp timestamp = results.get<nanodbc::timestamp>("test_datetime");
        nanodbc::timestamp timestamp2 = results.get<nanodbc::timestamp>("test_datetime2");
        list.push_back(db_status_entity(results.get<int>("test_int"),
                                                        results.get<string>("test_string"),
                                                        (bool)results.get<int>("test_bool"),
                                                        results.get<double>("test_float"),
                                                        TimeHelper::ToGregorianDate(timestamp),
                                                        TimeHelper::ToPosixTime(timestamp2)));
    }
    return list;
}

void db_status_sqlserver::SaveDbStatus(db_status_entity db_status)
{

    string sql = "\
    INSERT INTO [KGWS].[dbo].[test_table]\
    (\
        [test_int],\
        [test_string],\
        [test_bool],\
        [test_datetime],\
        [test_float],\
        [test_datetime2],\
        [test_null]\
    )\
    VALUES\
    (\
        ?,?,?,?,?,?,?\
     )\
    ;";

    vector<SqlParameter> parameters;
    parameters.push_back(SqlParameter{ 0,db_status.get_id() });
    parameters.push_back(SqlParameter{ 1,db_status.get_name() });
    parameters.push_back(SqlParameter{ 2,db_status.get_is_deleted() });
    parameters.push_back(SqlParameter{ 3,db_status.get_date_test() });
    parameters.push_back(SqlParameter{ 4,db_status.get_double_test() });
    parameters.push_back(SqlParameter{ 5,db_status.get_date_time_test() });
    nullptr_t null_test = nullptr;
    parameters.push_back(SqlParameter{ 6,null_test });

    std::unique_ptr<SqlserverHelper> helper(new SqlserverHelper);
    //helper->execute(sql, parameters);

    vector<SqlParameter> parameters2;
    const int A = 1;
    parameters2.push_back(SqlParameter{ 0,A });

    const string C = "b";
    parameters2.push_back(SqlParameter{ 1,C });

    const bool B = true;
    parameters2.push_back(SqlParameter{ 2,B });

    const boost::gregorian::date boost_date(2021, 1, 1);
    parameters2.push_back(SqlParameter{ 3,boost_date });

    const double E = 0.1;
    parameters2.push_back(SqlParameter{ 4,E });

    const boost::gregorian::date boost_date2(2021, 1, 1);
    boost::posix_time::time_duration td1(boost::posix_time::hours(12) + boost::posix_time::minutes(12) + boost::posix_time::seconds(12));
    boost::posix_time::ptime ptime(boost_date2, td1);
    parameters2.push_back(SqlParameter{ 5,ptime });

    nullptr_t null_test2 = nullptr;
    parameters2.push_back(SqlParameter{ 6,null_test2 });

    //string sql3 = "\
    //INSERT INTO [KGWS].[dbo].[test_table]\
    //(\
    //    [test_int],\
    //    [test_string],\
    //    [test_datetime]\
    //)\
    //VALUES\
    //(\
    //    ?,?,?\
    // )\
    //;";

    string sql3 = "\
    INSERT INTO [KGWS].[dbo].[test_table]\
    (\
        [test_int],\
        [test_string],\
        [test_bool],\
        [test_datetime],\
        [test_float],\
        [test_datetime2],\
        [test_null]\
    )\
    VALUES\
    (\
        ?,?,?,?,?,?,?\
     )\
    ;";
    //helper->execute_transaction(sql3, parameters2);
    vector<std::pair<std::string, vector<SqlParameter>>> querys;
    querys.push_back(std::make_pair(sql3, parameters2));
    querys.push_back(std::make_pair(sql3, parameters2));
    helper->execute_transaction(querys);
}


