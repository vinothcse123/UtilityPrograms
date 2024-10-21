import csv
import json
from datetime import datetime


# A list to store the expenses
expense_list = []

def add_expense():
    try:
        date_str = input("Enter the date of the expense (YYYY-MM-DD): ")
        date = datetime.strptime(date_str, '%Y-%m-%d').date()
        
        category = input("Enter the category of the expense (e.g., Food, Travel): ").capitalize()
        amount = float(input("Enter the amount spent: "))
        description = input("Enter a brief description of the expense: ")
        
        # Storing the expense in a dictionary
        expense = {
            'date': str(date),
            'category': category,
            'amount': amount,
            'description': description
        }
        
        # Adding the expense to the list
        expense_list.append(expense)
        print("Expense added successfully!\n")
    except ValueError:
        print("Invalid input. Please ensure the date is in YYYY-MM-DD format and the amount is numeric.")

def show_expenses():
    if expense_list:
        valid_expense_data = "\nCurrent Valid Expenses:\n"
        invalid_entries = 0
        for idx, expense in enumerate(expense_list, 1):
            # Validating required fields
            if all(k in expense and expense[k] for k in ['date', 'category', 'amount', 'description']):
                valid_expense_data += f"{idx}. {expense['date']} - {expense['category']} - ${expense['amount']:.2f} - {expense['description']}\n"
            else:
                invalid_entries += 1
        
        if invalid_entries > 0:
            valid_expense_data += f"\n{invalid_entries} expense(s) were incomplete and skipped.\n"
        print(valid_expense_data)
    else:
        print("No expenses to show.")


monthly_budget = 0.0

# Function to set the monthly budget
def track_budget():
    print("1. Set Budget")
    print("2. Analyze Budget")
        
    choice = input("Choose an option: ")
        
    if choice == '1':
        global monthly_budget
        try:
            # Ensure the budget is a positive number
            monthly_budget = input("Enter Budget: ")
            monthly_budget = float(monthly_budget)
            return f"Monthly budget set to ${monthly_budget:.2f}."
        except ValueError:
            return "Invalid input. Please enter a valid numeric budget."
    elif choice == '2':
        print(analyzeBudget())

    

# Function to calculate the total expenses recorded so far
def calculate_total_expenses():
    total = sum(expense['amount'] for expense in expense_list)
    return total

# Function to track budget and display the balance or a warning
def analyzeBudget():
    if monthly_budget == 0:
        return "Please set a monthly budget first."
    
    total_expenses = calculate_total_expenses()
    
    if total_expenses > monthly_budget:
        return f"Warning: You have exceeded your budget! You have spent ${total_expenses:.2f}, which is ${total_expenses - monthly_budget:.2f} over the budget."
    else:
        remaining_balance = monthly_budget - total_expenses
        return f"You have ${remaining_balance:.2f} left for the month."



# Function to get input and save to CSV
def save_to_csv(file_name):
    # Open the CSV file in append mode
    with open(file_name, mode='w', newline='') as file:
        writer = csv.writer(file)
        valid_expense_data=""
        
        if expense_list:
            fieldnames = expense_list[0].keys()
    
            # Create a writer object and write the header (field names)
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writeheader()

            # Write each dictionary (row) to the CSV file
            for row in expense_list:
                writer.writerow(row)
        else:
            print("No expenses to save.")


def read_from_csv(file_name):
    global expense_list
    expense_list = []
    # print("\nReading data from CSV file...\n")
    # # Open the CSV file in read mode
    with open(file_name, "r") as file:

        reader = csv.DictReader(file)

        for row in reader:
            # Convert the second column to float (assuming the second column is 'Age' for this example)
            row['amount'] = float(row['amount']) 
            expense_list.append(dict(row))
        
        

    
# File name to save the data
csv_file = 'personalExpense.csv'

def saveOrLoadExpense():
    print("1. Save Expense")
    print("2. Load Expenses")
        
    choice = input("Choose an option: ")
        
    if choice == '1':
        save_to_csv(csv_file)
    elif choice == '2':
        read_from_csv(csv_file)


# Sample menu-driven interface
def menu():
    while True:
        print("\n===========Personal Expense Tracker===========")
        print("1. Add an Expense")
        print("2. Show Expenses")
        print("3. Track Budget")
        print("4. Save or Load Expense")
        print("5. Exit")
        
        choice = input("Choose an option: ")
        
        if choice == '1':
            add_expense()
        elif choice == '2':
            show_expenses()
        elif choice == '3':
            track_budget()
        elif choice == '4':
            saveOrLoadExpense()
        elif choice == '5':
            print("Exiting the Expense Tracker.")
            break
        else:
            print("Invalid option. Please try again.")

# Starting the menu
menu()
