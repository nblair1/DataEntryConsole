#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <sstream>
#include <fstream>

#include <iostream>






using namespace std;

int main()
{
    cout << "Pres 1 to start the program" << endl;
    int mic;
    cin >> mic;

    while (true)
    {
        cout << "Enter 1 to see records by order of entry" << endl;
        cout << "Enter 2 to search for a specific record by plate number" << endl;
        cout << "Enter 3 to view all records" << endl;
        cout << "Enter 4 to insert record and print a pdf" << endl;
        cout << "Enter 5 to exit the program" << endl;
        int violation;
        int choice;
        cin >> choice;
        cin.ignore();

        try
        {
            // MySQL database connect
            sql::Driver* driver = get_driver_instance();
            // change each parameter to match that of your database
            sql::Connection* con = driver->connect("tcp://127.0.0.1:3039", "yourUsername", "yourPassword");
            con->setSchema("yourDatabase");

            switch (choice)
            {
            case 1:
            {
                // viewing by order
                // select query
                sql::Statement* stmt = con->createStatement();
                // execute the select query
                sql::ResultSet* res = stmt->executeQuery("SELECT * FROM parking_tickets ORDER BY date ASC");

                // printing results
                while (res->next())
                {

                    cout << "Issuing officer: " << res->getString("issuing_officer") << endl;
                    cout << "Date: " << res->getString("date") << endl;
                    cout << "Time: " << res->getString("time") << endl;
                    cout << "Location: " << res->getString("location") << endl;
                    cout << "Warning number: " << res->getInt("warning_number") << endl;
                    cout << "Plate number: " << res->getString("plate_number") << endl;
                    cout << "Vehicle description: " << res->getString("vehicle_description") << endl;
                    cout << endl;
                }

                delete res;
                delete stmt;
                break;
            }
            case 2:
            {
                // searching by matching plate number
                string plate_number;
                cout << "Enter the plate number: ";
                cin >> plate_number;
                // prepared statement
                sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM parking_tickets WHERE plate_number = ?");
                // bind the values
                pstmt->setString(1, plate_number);
                // Execute the prepared statement and get the results
                sql::ResultSet* res = pstmt->executeQuery();
                // Print the results
                if (res->next())
                {

                    cout << "Issuing officer: " << res->getString("issuing_officer") << endl;
                    cout << "Date: " << res->getString("date") << endl;
                    cout << "Time: " << res->getString("time") << endl;
                    cout << "Location: " << res->getString("location") << endl;
                    cout << "Warning number: " << res->getInt("warning_number") << endl;
                    cout << "Plate number: " << res->getString("plate_number") << endl;
                    cout << "Vehicle description: " << res->getString("vehicle_description") << endl;
                    cout << endl;
                }
                else
                {
                    cout << "No records found for plate number " << plate_number << endl;
                }
                delete res;
                delete pstmt;
                break;
            }
            case 3:
            {
                // all records
                // statement object instantiation 
                sql::Statement* stmt = con->createStatement();
                // Execute the SELECT query and get the results
                sql::ResultSet* res = stmt->executeQuery("SELECT * FROM parking_tickets");
                // Print the results
                while (res->next())
                {
                    cout << "Issuing officer: " << res->getString("issuing_officer") << endl;
                    cout << "Date: " << res->getString("date") << endl;
                    cout << "Time: " << res->getString("time") << endl;
                    cout << "Location: " << res->getString("location") << endl;
                    cout << "Warning number: " << res->getInt("warning_number") << endl;
                    cout << "Plate number: " << res->getString("plate_number") << endl;
                    cout << "Vehicle description: " << res->getString("vehicle_description") << endl;
                    cout << endl;
                }
                delete res;
                delete stmt;
                break;
            }
            case 4:
            {
                std::string issuing_officer, date, time, location, filename;
                while (true) {
                    std::cout << "Enter a file name: ";
                    std::getline(std::cin, filename);

                    // no spaces
                    if (std::find(filename.begin(), filename.end(), ' ') != filename.end()) {
                        std::cout << "Invalid filename. Filenames cannot contain spaces. Please try again." << std::endl;
                    }
                    // not null
                    else if (filename.empty()) {
                        std::cout << "Invalid filename. Please try again." << std::endl;
                    }
                    else {
                        break;
                    }
                }
                // validity for input constraint
                while (true) {
                    std::cout << "Enter the issuing officer: ";
                    std::getline(std::cin, issuing_officer);
                    // not null or not containing numerical vallue
                    if (issuing_officer.empty() || std::any_of(issuing_officer.begin(), issuing_officer.end(), ::isdigit)) {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                    else {
                        break;
                    }
                }
                
                // validity check
                while (true) {
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    std::getline(std::cin, date);

                    // Check if input is empty or in incorrect format
                    if (date.empty() || date.length() != 10 || date[4] != '-' || date[7] != '-') {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                    else {
                        break;
                    }
                }
                // time format
                while (true) {
                    std::cout << "Enter the time (HH:MM:SS): ";
                    std::cin >> time;
                    cin.ignore();
                    // not empty 
                    if (time.empty() || time.length() != 8 || time[2] != ':' || time[5] != ':') {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                    else {
                        break;
                    }
                }

                // validity check for location
                while (true) {
                    std::cout << "Enter the location: ";
                    std::getline(std::cin, location);
                    // Check if input is empty
                    if (location.empty()) {
                        std::cout << "Invalid input. Please try again." << std::endl;
                    }
                    else {
                        break;
                    }
                }
                // check if violation input is valid
// check if violation input is valid
                while (true) {
                    cout << "Enter the reason for the violation: " << endl;
                    cout << "1. Parked in Handicap Space without permit" << endl;
                    cout << "2. Parked in a marked no parking zone" << endl;
                    cout << "3. Parked in a fire zone" << endl;
                    cout << "4. Blocking access to vital infrastructure" << endl;
                    cout << "5. Improperly parked" << endl;
                    cout << "6. Overnight parking" << endl;
                    cout << "7. Parking with intent to solicit or advertise" << endl;

                    string input;
                    getline(cin, input);
                    stringstream ss(input);

                    // check if the input is a valid integer
                    if (!(ss >> violation)) {
                        // input is not an integer, display an error message and clear the error state
                        cout << "Please enter a valid integer between 1 and 7." << endl;
                        ss.clear();
                    }
                    //
                    else {
                        // check if the input is between 1 and 7
                        if (violation < 1 || violation > 7) {
                            cout << "Please enter a valid integer between 1 and 7." << endl;
                        }
                        else {
                            // input is valid, exit the loop
                            break;
                        }
                    }

                    // clear the contents of the stringstream object
                    ss.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                string violation_description;
                if (violation == 1) {
                    violation_description = "Parked in Handicap Space without permit";
                }
                else if (violation == 2) {
                    violation_description = "Parked in a marked no parking zone";
                }
                else if (violation == 3) {
                    violation_description = "Parked in a fire zone";
                }
                else if (violation == 4) {
                    violation_description = "Blocking access to vital infrastructure";
                }
                else if (violation == 5) {
                    violation_description = "Improperly parked";
                }
                else if (violation == 6) {
                    violation_description = "Overnight parking";
                }
                else if (violation == 7) {
                    violation_description = "Parking with intent to solicit or advertise";
                }
                // input without hefty input constraints
                std::string plate_number, vehicle_description;

                
                std::cout << "Enter plate number: ";
                std::getline(std::cin, plate_number);
                std::cout << "Enter vehicle description: ";
                std::getline(std::cin, vehicle_description);

                int warning_number = 1;

                // statement object
                sql::Statement* stmt = con->createStatement();
                
                // for rows that have the same plate number as the one the user entered
                std::string query = "SELECT MAX(warning_number) AS max_warning_number FROM parking_tickets WHERE plate_number = '" + plate_number + "'";
                sql::ResultSet* res = stmt->executeQuery(query);

                if (res->next()) {
                    // get the maximum value of the warning_number column
                    warning_number = res->getInt("max_warning_number") + 1;
                }

                delete res;
                delete stmt;


                // prepared statement for insert
                sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO parking_tickets (issuing_officer, date, time, location, warning_number, plate_number, vehicle_description, violation, violation_description) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

                // bind valuses
                pstmt->setString(1, issuing_officer);
                pstmt->setString(2, date);
                pstmt->setString(3, time);
                pstmt->setString(4, location);
                pstmt->setInt(5, warning_number);
                pstmt->setString(6, plate_number);
                pstmt->setString(7, vehicle_description);
                pstmt->setInt(8, violation);
                pstmt->setString(9, violation_description);

                
                pstmt->executeUpdate();

                // delete the prepared statement when you are done with it
                delete pstmt;
                // PDF file for the current record using wkhtmltopdf
                std::stringstream htmlStream;
                htmlStream << "<center><h1 style='font-size:36px; color:red'>Parking Violation</h1></center>" << std::endl;
                htmlStream << "<p style='font-size:24px;'>You are parked on private property. As such, you are liable for the expense of possible towing for: " << violation_description << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Issuing Officer: " << issuing_officer << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Reason for Violation: " << violation << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Date: " << date << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Time: " << time << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Location: " << location << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Warning Number: " << warning_number << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Plate Number: " << plate_number << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Vehicle Description: " << vehicle_description << "</p>" << std::endl;
                htmlStream << "<br>" << std::endl;
                
                

                htmlStream << "<p style='font-size:24px'>_______________________________</p>" << std::endl;
                htmlStream << "<p style='font-size:24px'>Signature</p>" << std::endl;
                
               
                htmlStream << "<p style='font-size:30px'>Censor Security</p></center>" << std::endl;
                htmlStream << "<br>" << std::endl;


                htmlStream << "<center><h1 style='font-size:36px; color:red'>Parking Violation</h1></center>" << std::endl;
                htmlStream << "<p style='font-size:24px;'>You are parked on private property. As such, you are liable for the expense of possible towing for: " << violation_description << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Issuing Officer: " << issuing_officer << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Date: " << date << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Time: " << time << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Location: " << location << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Warning Number: " << warning_number << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Plate Number: " << plate_number << "</p>" << std::endl;
                htmlStream << "<p style='text-decoration: underline;'>Vehicle Description: " << vehicle_description << "</p>" << std::endl;
                htmlStream << "<br>" << std::endl;
                
                htmlStream << "<p style='font-size:24px'>_______________________________</p>" << std::endl;
                htmlStream << "<p style='font-size:24px'>Signature</p>" << std::endl;
                
                htmlStream << "<p style='font-size:24px'>Censor Security</p>" << std::endl;
                htmlStream << "<br>" << std::endl;
              

               

                // HTML to a file
                std::ofstream htmlFile(filename + ".html");
                htmlFile << htmlStream.str();
                htmlFile.close();
                // HTML to a PDF using wkhtmltopdf
                std::stringstream commandStream;
                // replace filename path with what matches your target
                commandStream << "wkhtmltopdf.exe " << filename << ".html C:\\/Users\\/yourPath\\/Example\\/wkhtmltopdf\\/pdfs\\/" << filename << ".pdf";
                int ret = std::system(commandStream.str().c_str());
                if (ret != 0) {
                    std::cerr << "Error generating PDF. Return value: " << ret << std::endl;
                }






                cout << "PDF saved to " << filename << ".pdf" << endl;

                break;
            }
            case 5:
            {
                // exit 

                return(0);
            }
            }
            delete con;
        }
        catch (sql::SQLException& e)
        {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }

    }
    return(0);
}



