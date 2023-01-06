# DataEntryConsole
This is a .cpp program that integrates CRUD-like operations for a MySQL Database. It also auto generates parking tickets based on User Inputs. This simplifies data entry for users who do not have a technical background and do not wish to interact with tools, such as SQL Workbench directly. Additionally, there are explicit input constraints that assure quality, valid data is entered in a consistent format. 

# Example of simple console

![Screenshot (646)](https://user-images.githubusercontent.com/112766091/211091404-9ed2dec2-c3b2-4ec7-a0e6-4e99a4cf5f3a.png)
# Example of PDF auto-generating

![Screenshot (648)](https://user-images.githubusercontent.com/112766091/211091445-46630265-06ad-4304-b789-2461d3b2354a.png)
# Showing accurate reflection on a mySQL Server (Local Instance).

![Screenshot (650)](https://user-images.githubusercontent.com/112766091/211091912-a4cc5d1d-4191-47eb-8825-c64846eec62d.png)

# Dependencies
This project uses the MySQL C++ Connector and wkhtmltopdf libraries. In order to build and run this project, you will need to download and install these libraries.

MySQL C++ Connector
To download the MySQL C++ Connector, go to https://dev.mysql.com/downloads/connector/cpp/. Follow the instructions on the page to download and install the library.

wkhtmltopdf
To download wkhtmltopdf, go to https://wkhtmltopdf.org/downloads.html. Follow the instructions on the page to download and install the library.

Once you have downloaded and installed the necessary libraries, you will need to include them in your project. In Visual Studio, go to the "Project" menu and select "Properties". Under "Configuration Properties", select "Linker" and then "Input". In the "Additional Dependencies" field, add the path to the .lib files for the MySQL C++ Connector and wkhtmltopdf libraries.
