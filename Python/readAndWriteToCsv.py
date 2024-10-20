import csv

# Function to get input and save to CSV
def save_to_csv(file_name):
    # Open the CSV file in append mode
    with open(file_name, mode='a', newline='') as file:
        writer = csv.writer(file)

        # Get user input
        while True:
            name = input("Enter Name: ")
            description = input("Enter Description: ")
            amount = input("Enter Amount: ")

            # Write data to CSV file
            writer.writerow([name, description, amount])

            # Ask if user wants to add more data
            another = input("Do you want to add another record? (yes/no): ").lower()
            if another != 'yes':
                break

# Function to read and display CSV file
def read_from_csv(file_name):
    print("\nReading data from CSV file...\n")
    # Open the CSV file in read mode
    with open(file_name, mode='r') as file:
        reader = csv.reader(file)
        for row in reader:
            print(f"Name: {row[0]}, Description: {row[1]}, Amount: {row[2]}")

# File name to save the data
csv_file = 'user_data.csv'

# Save input data to CSV
save_to_csv(csv_file)

# Read and display the saved data
read_from_csv(csv_file)
