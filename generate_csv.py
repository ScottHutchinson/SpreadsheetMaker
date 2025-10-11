import csv
import random
import string

# File specifications
num_rows = 10000
num_cols = 600
num_unique_strings = 100000
filename = 'large_string_data.csv'

# Generate the pool of 100,000 unique strings
print("Generating pool of unique strings...")
string_pool = []
for i in range(num_unique_strings):
    # Create a unique string, e.g., "string_0", "string_1", etc.
    # We use a mix of letters and numbers to make them look like real data
    unique_part = f"str_{i:06d}"
    random_part = ''.join(random.choices(string.ascii_letters + string.digits, k=5))
    string_pool.append(unique_part + random_part)

print(f"Pool of {len(string_pool)} strings created.")
print(f"Writing to file: {filename}")

# Create and write to the CSV file
with open(filename, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)

    # Write the header row
    header = [f'col_{i+1}' for i in range(num_cols)]
    writer.writerow(header)

    # Write the data rows
    for i in range(num_rows):
        # Create a row of 600 randomly selected strings from the pool
        row = random.choices(string_pool, k=num_cols)
        writer.writerow(row)
        
        # Print progress to the console
        if (i + 1) % 1000 == 0:
            print(f"Finished writing row {i + 1} of {num_rows}...")

print(f"Successfully created '{filename}' with {num_rows} rows and {num_cols} columns.")
print(f"The file size will be approximately {round(num_rows * num_cols * 15 / 1024**2, 2)} MB.") # Estimate assuming 15 bytes per string plus commas.
