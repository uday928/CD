def compute_first(grammar, non_terminal, first, visited):
    if non_terminal in visited:
        return first[non_terminal]
    visited.add(non_terminal)
    first_set = set()

    for production in grammar[non_terminal]:
        for symbol in production:
            if symbol.islower():  # Terminal
                first_set.add(symbol)
                break
            elif symbol.isupper():  # Non-terminal
                sub_first = compute_first(grammar, symbol, first, visited)
                first_set.update(sub_first - {'ε'})
                if 'ε' not in sub_first:
                    break
            else:  # Epsilon (empty string)
                first_set.add('ε')
                break
    first[non_terminal] = first_set
    return first_set

def compute_follow(grammar, start_symbol, first, follow):
    follow[start_symbol].add('$')  # Start symbol gets EOF marker
    for non_terminal, productions in grammar.items():
        for production in productions:
            for i, symbol in enumerate(production):
                if symbol.isupper():  # Non-terminal
                    rest = production[i + 1:]
                    if rest:
                        rest_first = set()
                        for r in rest:
                            if r.islower():  # Terminal
                                rest_first.add(r)
                                break
                            elif r.isupper():  # Non-terminal
                                rest_first.update(first[r] - {'ε'})
                                if 'ε' not in first[r]:
                                    break
                            else:  # Epsilon
                                rest_first.add('ε')
                                break
                        follow[symbol].update(rest_first - {'ε'})
                    if not rest or 'ε' in rest_first:
                        follow[symbol].update(follow[non_terminal])

def build_parsing_table(grammar, first, follow):
    table = {}
    for non_terminal, productions in grammar.items():
        table[non_terminal] = {}
        for production in productions:
            first_set = set()
            for symbol in production:
                if symbol.islower():  # Terminal
                    first_set.add(symbol)
                    break
                elif symbol.isupper():  # Non-terminal
                    first_set.update(first[symbol] - {'ε'})
                    if 'ε' not in first[symbol]:
                        break
                else:  # Epsilon
                    first_set.add('ε')
                    break
            for terminal in first_set - {'ε'}:
                table[non_terminal][terminal] = production
            if 'ε' in first_set:
                for terminal in follow[non_terminal]:
                    table[non_terminal][terminal] = production
    return table

def parse_string(input_string, table, start_symbol):
    stack = ['$']
    stack.append(start_symbol)
    input_string += '$'
    i = 0

    while stack:
        top = stack.pop()
        if top == '$' and input_string[i] == '$':
            print("String is successfully parsed!")
            return True
        elif top.islower() or top == '$':
            if top == input_string[i]:
                i += 1
            else:
                print(f"Error: Expected {top} but found {input_string[i]}")
                return False
        elif top.isupper():
            if input_string[i] in table[top]:
                production = table[top][input_string[i]]
                print(f"Applying rule: {top} -> {' '.join(production)}")
                for symbol in reversed(production):
                    if symbol != 'ε':
                        stack.append(symbol)
            else:
                print(f"Error: No rule for {top} with lookahead {input_string[i]}")
                return False
    print("Error: Stack is empty but input is not fully consumed!")
    return False

if __name__ == "__main__":
    grammar = {}
    print("Enter the grammar (type 'END' to stop):")
    while True:
        try:
            line = input().strip()
            if line == 'END':
                break
            head, productions = line.split('->')
            head = head.strip()
            grammar[head] = [prod.strip().split() for prod in productions.split('|')]
        except Exception as e:
            print(f"Error in input: {e}")

    start_symbol = input("Enter the start symbol: ").strip()
    input_string = input("Enter the string to parse: ").strip()

    first = {non_terminal: set() for non_terminal in grammar}
    follow = {non_terminal: set() for non_terminal in grammar}

    # Compute FIRST sets
    for non_terminal in grammar:
        compute_first(grammar, non_terminal, first, set())

    # Compute FOLLOW sets
    for _ in range(len(grammar)):
        compute_follow(grammar, start_symbol, first, follow)

    # Build the parsing table
    table = build_parsing_table(grammar, first, follow)

    # Display the FIRST sets, FOLLOW sets, and Parsing Table
    print("FIRST Sets:")
    for non_terminal, first_set in first.items():
        print(f"{non_terminal}: {first_set}")

    print("\nFOLLOW Sets:")
    for non_terminal, follow_set in follow.items():
        print(f"{non_terminal}: {follow_set}")

    print("\nParsing Table:")
    for non_terminal, entries in table.items():
        for terminal, production in entries.items():
            print(f"{non_terminal} -> {terminal}: {' '.join(production)}")

    # Parse the input string
    print("\nParsing String:", input_string)
    parse_string(input_string, table,start_symbol)


# I/P:
# Enter the grammar (type 'END' to stop):
# E -> T E'
# E' -> + T E' | ε
# T -> F T'
# T' -> * F T' | ε
# F -> ( E ) | id
# END
# Enter the start symbol: E
# Enter the string to parse: id + id * id
