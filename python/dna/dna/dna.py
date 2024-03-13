import csv
import sys
import re


def main():

    # TODO: Check for command-line usage
    arguments = sys.argv
    if len(sys.argv) != 3:
        print("Usage: python dna.py database file")

    # TODO: Read database file into a variable
    database = []
    with open(arguments[1],'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(arguments[2],'r') as file:
        dna = file.read().strip()
    # TODO: Find longest match of each STR in DNA sequence
    #create a list of all dna combination to find, read all the field name into list except when it's 'name'
    STR_list = [field for field in reader.fieldnames if field != 'name']
    #Create a dictionary to store number of STR of the longest match
    STR_counts = {substrings:0 for substrings in STR_list}
    for substrings in STR_counts:
        #use the longest_match to assign the number of longest STR streak or something to the corresponding STR in the list
        STR_counts[substrings] = longest_match(dna, substrings)
    # TODO: Check database for matching profiles
    for row in database:
        #find all the match (match is true if only all the number of STR are the same in the database row and the text)
        match = all(int(STR_counts[substrings]) == int(row[substrings]) for substrings in STR_counts.keys() if substrings in row)
        if match:
            print(f"{row['name']}")
            return
    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
