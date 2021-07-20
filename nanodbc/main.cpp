// nanodbc.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <iostream>
#include <boost/version.hpp>
#include "db_status_sqlserver.h"
#include <exception>
#include <stdlib.h>
#include <thread>
#include <boost/timer/timer.hpp>

#include <string>
#include <fstream>
#include <sstream>

using namespace std;
void show(nanodbc::result& results);
void ShowDBBackupStatus();
void csvCreateDbBackupLog(std::string path);
void csvCreate(std::string path);

int main()
{
    std::cout << "Hello World!\n";
    std::cout << "boostバージョン:" << BOOST_VERSION << std::endl;
    std::cout << "boostライブラリバージョン:" << BOOST_LIB_VERSION << std::endl;

    std::string output_csv_file_path = "C:\\Users\\akira\\OneDrive\\デスクトップ\\test.csv";
    std::string output_csv_file_path_tabledata_count = "C:\\Users\\akira\\OneDrive\\デスクトップ\\test2.csv";

    try {
        //ShowDBBackupStatus();
        //csvCreateDbBackupLog(output_csv_file_path);
        csvCreate(output_csv_file_path_tabledata_count);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void csvCreate(std::string path) {
    std::unique_ptr<db_status_sqlserver> db_status(new db_status_sqlserver());
    auto v = db_status->getTableDataCount();
    std::ofstream ofs_csv_file(path);
    ofs_csv_file << "db_name" << ',' << "table_name" << ',' << "row_count"<< "reserved_page_count_kb" << endl;
}

void csvCreateDbBackupLog(std::string path) {
    std::unique_ptr<db_status_sqlserver> db_status(new db_status_sqlserver());
    auto v = db_status->GetDbBackupLogAll();
    std::ofstream ofs_csv_file(path);
    ofs_csv_file << "db_name" << ',' << "create_at" << ',' << "fullbackup_at" << endl;

    for (auto itr = v.begin(); itr != v.end(); ++itr) {
        ofs_csv_file << itr._Ptr->Get_dbName() << ',';
        ofs_csv_file << itr._Ptr->Get_displayCreateDate() << ',';
        ofs_csv_file << itr._Ptr->Get_displayFullBackupDate() << ',';
        ofs_csv_file << endl;
    }
}

void ShowDBBackupStatus() {
    std::unique_ptr<db_status_sqlserver> db_status(new db_status_sqlserver());
    auto v = db_status->GetDbBackupLogAll();
    for (auto itr = v.begin(); itr != v.end(); ++itr) {
        cout << itr._Ptr->Get_dbName() << " | " << itr._Ptr->Get_displayCreateDate() << " | " << itr._Ptr->Get_displayFullBackupDate() << endl;
    }
}

void show(nanodbc::result& results)
{
    const short columns = results.columns();
    long rows_displayed = 0;

    cout << "\nDisplaying " << results.affected_rows() << " rows "
        << "(" << results.rowset_size() << " fetched at a time):" << endl;

    // show the column names
    cout << "row\t";
    for (short i = 0; i < columns; ++i)
        cout << results.column_name(i) << "\t";
    cout << endl;

    // show the column data for each row
    while (results.next())
    {
        cout << rows_displayed++ << "\t";
        for (short col = 0; col < columns; ++col)
            cout << "(" << results.get<string>(col, "null") << ")\t";
        cout << endl;
    }
}

