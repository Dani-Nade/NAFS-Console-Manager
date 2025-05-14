# NAFS-Console-Manager

A C++ console application for managing airline flights and bookings with two user roles—**Admin** and **Passenger**—built and tested on Windows.

## Features

- **Role-based menus**  
  - **Admin**: add new routes, update schedules, restrict seats, update inquiry contact  
  - **Passenger**: register (with masked password input), update details, view most-visited country, book flights  
- **Password security**:  
  - Masked entry via `_getch()` (conio.h)  
  - Enforced strength: ≥8 chars, uppercase, lowercase, digit, special  
- **Persistent storage**:  
  - `Users.txt` for passenger records  
  - `Inquiry.txt` for airline contact info  
- **Windows console UX**:  
  - `system("cls")` for screen-clearing  
  - `Sleep()` pauses  
- **Simple validation**: CNIC format, financial detail length, unique usernames/CNICs  

## Prerequisites

- Windows 10+  
- A C++ compiler (Visual Studio or MinGW/g++)  
- No external libraries required  

## Building

Open a Developer PowerShell or CMD in the project folder and run:

```batch
g++ -std=c++11 main.cpp 8e6e92d2-3c37-4737-85e6-1cf3934f0646.cpp -o NAFS.exe
(If you split your code into multiple .cpp files, list them all on the command line.)

Running
Make sure the executable and the data files are in the same folder:

arduino
Copy
Edit
NAFS.exe
Users.txt   (will be created on first run)
Inquiry.txt (will be created on first run)
From PowerShell or CMD:

batch
Copy
Edit
.\NAFS.exe
Follow the on-screen menu prompts.

File Structure
bash
Copy
Edit
.
├── main.cpp                   # `main()` + menu loops
├── NAFSSystem.cpp             # core logic (User/Admin/Passenger/Flight classes)
├── NAFSSystem.hpp             # class declarations
├── Users.txt                  # passenger data (auto-created)
└── Inquiry.txt                # airline inquiry info (auto-created)
Extending
Swap text files for a database backend.

Add more validation rules or internationalization.

Replace system("cls")/Sleep() with a cross-platform library for broader OS support.

License: MIT © 2025