
//SOURCE CODE OF PROJECT: 
#include <iostream> 
#include <conio.h> 
#include <ctime> 
#include <fstream> 
#include <vector> 
#include "cstm_queue.h" 
#include "custom_list.h" 
using namespace std;
string current_time() 
{ 
 //This Function Returns Current Time as a String// 
time_t now = time(0);
string crnt_time = ctime(&now);
 //Trimming The String To Remove Day 
 crnt_time = crnt_time.substr(4, crnt_time.length() - 5); //Also Removing an End-Line 
Character From The End 
return crnt_time;
} 
//Following Function Saves an order in a File 
void save_order(SingleLL<string> order, int bill) 
{ 
ofstream Fout("Orders.csv", ios::app); // Opening File in Append Mode
Fout << current_time() << ',';
Fout << bill;
for (int i = 0; i < order.size(); i++)
 { 
 Fout << ',' << order.at(i);
 } 
 Fout << "\n";
Fout.close();
} 
//Following Function Loads previous orders from a File 
void load_orders() 
{ 
ifstream Fin("Orders.csv");
 if (!Fin.is_open()) 
 { 
 cout << "No Previous Record Found";
 getch();
 return;
 } 
 cout << "\n Time" 
 << "\t\t" 
 << "Bill" 
 << "\t\t" 
 << "Order" << endl;
string temp;
 while (!Fin.eof()) 
 { 
 getline(Fin, temp, ','); //Time
 cout << temp << '\t';
 getline(Fin, temp, ','); //Price
 cout << temp << '\t';
 getline(Fin, temp);
 cout << temp << '\n'; // Order
 } 
getch();
getch();
} 
// Define a structure for Food 
struct Food 
{ 
string name;
string price;
string category;
};
// Define a structure for User(Base Class) 
struct User 
{ 
string Name;
string ID;
string Password;
 // Function to load the menu from file 
 SingleLL<Food> loadMenu() 
 { 
 SingleLL<Food> menu;
 ifstream Fin("Menu.csv");
 if (Fin.is_open()) 
 { 
 while (!Fin.eof()) 
 { 
 Food temp;
 getline(Fin, temp.name, ',');
 getline(Fin, temp.price, ',');
 getline(Fin, temp.category);
 menu.push_back(temp);
 } 
 Fin.close();
 } 
 return menu;
 } 
 // Function to view the menu 
 void viewMenu() 
 { 
 SingleLL<Food> menu = loadMenu();
 // Extract unique categories 
 SingleLL<string> categories;
 for (int i = 0; i < menu.length(); i++)
 { 
 Food food = menu.at(i);
 bool found = false;
 for (int i = 0; i < categories.length(); i++)
 { 
 string cat = categories.at(i);
 if (cat == food.category) 
 { 
 found = true;
 break;
 } 
 } 
 if (!found) 
 { 
 categories.push_back(food.category);
 } 
 } 
 // Display categories 
 cout << "Menu Categories:\n";
 for (size_t i = 0; i < categories.size()-1; ++i)
 { 
 cout << i + 1 << ". " << categories.at(i) << endl;
 } 
 // Choose a category 
 int categoryChoice;
 cout << "Choose a category (enter the corresponding number): ";
 cin >> categoryChoice;
 fflush(stdin);
 if (categoryChoice >= 1 && categoryChoice <= categories.size()) 
 { 
 system("cls");
 string chosenCategory = categories.at(categoryChoice - 1);
 cout << "Menu (" << chosenCategory << "):\n";
 for (int i = 0; i < menu.length(); i++)
 { 
 Food food = menu.at(i);
 if (food.category == chosenCategory) 
 { 
 cout << "- " << food.name << " (Rs " << food.price << 
")\n";
 } 
 } 
 cout << endl;
 } 
 else 
 { 
 cout << "Invalid category choice.\n";
 } 
 system("pause");
 } 
};
// Function to handle user login 
User login() 
{ 
 SingleLL<User> users;
 // Adding default users 
 users.push_back({"Admin", "Admin", "Admin"});
 // Load users from file 
 ifstream userFile("Employees.csv");
 if (userFile.is_open()) 
 { 
 while (!userFile.eof()) 
 { 
 User temp;
 getline(userFile, temp.Name, ',');
 getline(userFile, temp.ID, ',');
 getline(userFile, temp.Password);
 users.push_back(temp);
 } 
 userFile.close();
 } 
 // Actual login process 
 while (true) 
 { 
 system("cls");
 string id;
 string pass = "";
 cout << "Enter Your ID: ";
 getline(cin, id);
 if (id.empty()) 
 { 
 cout << "Incorrect ID or Password" << endl;
 getch();
 continue;
 } 
 bool foundUser = false;
 for (int i = 0; i < users.length(); i++)
 { 
 User user = users.at(i);
 if (id == user.ID) 
 { 
 pass.resize(user.Password.length());
 cout << "Enter Password: ";
 for (int i = 0; i < pass.length(); i++)
 { 
 pass[i] = getch();
 if (pass[i] == '\b') 
 { 
 cout << '\b';
 i -= 2;
 } 
 else 
 { 
 cout << "*";
 } 
 } 
 if (pass == user.Password) 
 { 
 return user;
 } 
 else 
 { 
 foundUser = true; // User found, but password mismatch
 break;
 } 
 } 
 } 
 if (!foundUser) 
 { 
 cout << "\nIncorrect ID or Password" << endl;
 getch();
 } 
 } 
} 
// Class for Admin, derived from User 
class Admin : public User 
{ 
 public: 
 Admin() 
 { 
 Name = "Admin";
 } 
 // Function to display admin menu 
 void display() 
 { 
 while (true) 
 { 
 system("cls");
 int ch;
 cout<<"\t\t----- Welcome To Admin's Panel -----\n";
 cout << "1. View Menu" << endl;
 cout << "2. Change Menu" << endl;
 cout << "3. Manage Employees" << endl;
 cout << "4. View Previous Orders" << endl;
 cout << "5. Sign Out" << endl;
 cout << "Enter Your Choice: ";
 cin >> ch;
 fflush(stdin);
 switch (ch) 
 { 
 case 1: 
 viewMenu();
 break;
 case 2: 
 manageMenu();
 break;
 case 3: 
 manageEmployees();
 break;
 case 4: 
 load_orders();
 break;
 case 5: 
 fflush(stdin);
 return;
 default: 
 cout << "Invalid option, please try again." << endl;
 } 
 } 
 } 
 private: 
 // Function to manage the menu for admin 
 void manageMenu() 
 { 
 system("cls");
 int choice;
 cout << "1. Add Food Item" << endl;
 cout << "2. Remove Food Item" << endl;
 cout << "3. Back" << endl;
 cout << "Enter your choice: ";
 cin >> choice;
 fflush(stdin);
 switch (choice) 
 { 
 case 1: 
 addFoodItem();
 break;
 case 2: 
 removeFoodItem();
 break;
 case 3: 
 return;
 default: 
 cout << "Invalid option, please try again." << endl;
 } 
 } 
 // Function to manage employees for admin 
 void manageEmployees() 
 { 
 system("cls");
 int choice;
 cout << "1. Add Employee" << endl;
 cout << "2. Remove Employee" << endl;
 cout << "3. Back" << endl;
 cout << "Enter your choice: ";
 cin >> choice;
 fflush(stdin);
 switch (choice) 
 { 
 case 1: 
 addEmployee();
 break;
 case 2: 
 removeEmployee();
 break;
 case 3: 
 return;
 default: 
 cout << "Invalid option, please try again." << endl;
 } 
 } 
 // Function to add an employee 
 void addEmployee() 
 { 
 User newEmployee;
 cout << "Enter Employee Name: ";
 fflush(stdin);
 getline(cin, newEmployee.Name);
 cin.clear();
 cout << "Enter Employee ID: ";
 getline(cin, newEmployee.ID);
 cin.clear();
 cout << "Enter Employee Password: ";
 getline(cin, newEmployee.Password);
 cin.clear();
 ofstream Fout("Employees.csv", ios::app);
 if (Fout.is_open()) 
 { 
 Fout << newEmployee.Name << "," << newEmployee.ID << "," << 
newEmployee.Password << endl;
 Fout.close();
 cout << "Employee added successfully." << endl;
 getch();
 } 
 else 
 { 
 cout << "Unable to open file." << endl;
 } 
 } 
 // Function to remove an employee 
 // Function to remove an employee 
void removeEmployee() 
{ 
 system("cls");
 int choice;
 cout << "List of Employees:\n";
 // Display the list of employees with numbers 
 SingleLL<User> employees;
 ifstream Fin("Employees.csv");
 if (Fin.is_open()) 
 { 
 int count = 1;
 while (!Fin.eof()) 
 { 
 User temp;
 getline(Fin, temp.Name, ',');
 if (Fin.eof()) // Stop reading when reaching the end of the file 
 break;
 getline(Fin, temp.ID, ',');
 getline(Fin, temp.Password);
 // Display employee details with numbers 
 cout << count << ". " << temp.Name << " (ID: " << temp.ID << ")\n";
 employees.push_back(temp);
 count++;
 } 
 Fin.close();
 } 
 // Ask admin to choose the number of the employee to remove 
 cout << "Enter the number of the employee to remove (0 to go back): ";
 cin >> choice;
 fflush(stdin);
 if (choice >= 1 && choice <= employees.length()) 
 { 
 User empToRemove = employees.at(choice - 1);
 SingleLL<User> newEmployees;
 for (int i = 0; i < employees.length(); i++)
 { 
 if (i != choice - 1) 
 { 
 newEmployees.push_back(employees.at(i));
 } 
 } 
 ofstream Fout("Employees.csv");
 for (int i = 0; i < newEmployees.length(); i++)
 { 
 User emp = newEmployees.at(i);
 Fout << emp.Name << "," << emp.ID << "," << emp.Password << '\n';
 } 
 Fout.close();
 cout << "Employee removed successfully." << endl;
 } 
 else if (choice != 0) 
 { 
 cout << "Invalid choice, please try again." << endl;
 } 
 cout << "Press any key to go back.";
 getch();
} 
 // Function to add a food item to the menu 
 void addFoodItem() 
 { 
 Food newFood;
 cout << "Enter Food Name: ";
 fflush(stdin);
 getline(cin, newFood.name);
 cin.clear();
 cout << "Enter Food Price: ";
 getline(cin, newFood.price);
 cin.clear();
 cout << "Enter Food Category: ";
 getline(cin, newFood.category);
 cin.clear();
 ofstream Fout("Menu.csv", ios::app);
 if (Fout.is_open()) 
 { 
 Fout << newFood.name << "," << newFood.price << "," << 
newFood.category << '\n';
 Fout.close();
 cout << "Food item added successfully." << endl;
 getch();
 } 
 else 
 { 
 cout << "Unable to open file." << endl;
 } 
 } 
 // Function to remove a food item from the menu 
 void removeFoodItem() 
{ 
 
 SingleLL<Food> menu = loadMenu();
 cout << "Menu:\n";
 for (int i = 0; i < menu.size()-1; ++i)
 { 
 cout << i + 1 << ". " << menu.at(i).name << " (Rs " << 
menu.at(i).price << ") - " << menu.at(i).category << endl;
 } 
 
 int choice;
 cout << "Select the number of the food item to remove: ";
 cin >> choice;
 fflush(stdin);
 if (choice >= 1 && choice <= menu.size()) 
 { 
 Food foodToRemove = menu.at(choice - 1);
 SingleLL<Food> newMenu;
 for (int i = 0; i < menu.size(); i++)
 { 
 if (i != choice - 1) 
 { 
 newMenu.push_back(menu.at(i));
 } 
 } 
 ofstream Fout("Menu.csv");
 for (int i = 0; i < newMenu.size(); i++)
 { 
 Food food = newMenu.at(i);
 Fout << food.name << "," << food.price << "," << food.category << endl;
 } 
 Fout.close();
 cout << "Food item removed successfully." << endl;
 } 
 else 
 { 
 cout << "Invalid choice, please try again." << endl;
 } 
 cout << "Press any key to go back.";
 getch();
} 
};
// Class for Employee, derived from User 
class Employee : public User 
{ 
 public: 
Queue<string> pending;
 Employee() 
 { 
 Name = "Employee";
 ID = "Employee";
 Password = "Employee";
 } 
 // Function to display employee menu 
 void display() 
 { 
 while (true) 
 { 
 system("cls");
 int ch;
 cout << "\t\t----- Welcome To Employee's Panel -----\n" 
 << "1. View Menu\n" 
 << "2. Take Order\n" 
 << "3. View Pending Orders\n" 
 << "4. Sign Out\n" 
 << "Enter your choice: ";
 cin >> ch;
 fflush(stdin);
 switch (ch) 
 { 
 case 1: 
 viewMenu();
 break;
 case 2: 
 takeOrder();
 break;
 case 3: 
 view_queue();
 break;
 case 4: 
 return;
 break;
 default: 
 cout << "Invalid option, please try again." << endl;
 } 
 } 
 } 
 private: 
 // Function to take an order 
 void takeOrder() 
 { 
 SingleLL<Food> menu = loadMenu();
 SingleLL<string> order;
 double totalBill = 0.0;
 while (true) 
 { 
 system("cls");
 cout << "\t\t-----Menu-----\n";
 for (int i = 0; i < menu.size()-1; ++i)
 { 
 cout << i + 1 << ". " << menu.at(i).name << " (Rs " << 
menu.at(i).price << ") - " << menu.at(i).category << endl;
 } 
 int choice;
 cout << "Enter the item number to add to the order (0 to finish): ";
 cin >> choice;
 fflush(stdin);
 if (choice >= 1 && choice <= menu.size()) 
 { 
 totalBill += stod(menu.at(choice - 1).price); //Adding price to 
bill 
 order.push_back(menu.at(choice - 1).name); //Saving the 
choice in a different list 
 cout << "Item added to the order.\n";
 } 
 else if (choice == 0) 
 { 
 break;
 } 
 else 
 { 
 cout << "Invalid item number, please try again.\n";
 } 
 } 
 cout << "Total bill amount: Rs " << totalBill << endl;
 cout << "Thanks For Coming By....."<<endl;
 save_to_queue(order);
 save_order(order, totalBill);
 system("pause");
 } 
 void save_to_queue(SingleLL<string> order) 
 { 
 string full_order = "";
 for (int i = 0; i < order.length(); i++)
 { 
 full_order += order.at(i);
 full_order += ", ";
 } 
 pending.enqueue(full_order);
 } 
 void view_queue() 
 { 
 char ch;
 pending.display();
 cout << "Press 1 to Pop Remove The Oldest Order" << endl;
 cout << "Press any other key to go Back" << endl;
 ch = getch();
 ch = getch();
 if (ch == '1') 
 { 
 //if queue is empty 
 if (pending.dequeue()) 
 ;
 cout << "Order Removed Successfully";
 getch();
 return;
 } 
 else 
 { 
 return;
 } 
 } 
};
// Main function 
int main() 
{ 
 while (true) 
 { 
 system("cls");
 
 cout<<"\t\t----- Welcome To Our Cafe -----\n";
 cout<<"\nPlease Sign in Here By Pressing any Key\n";
 getch();
 
 User user = login();
 if (user.Name == "Admin") 
 { 
 Admin admin;
 admin.display();
 } 
 else 
 { 
 Employee employee;
 employee.display();
 } 
 system("cls");
 cout << "Signed out Successfully";
 fflush(stdin);
 getch();
 } 
return 0;
} 
