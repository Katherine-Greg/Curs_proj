import ctypes

libc = ctypes.CDLL("projects\\c_dll\\bin\\c_dll.dll")


val_input = libc.valid_int

total = libc.total_amount_of_questions

check = libc.check_and_find_amount
check.argtypes = [ctypes.c_int, ctypes.c_int,]

make_bilets = libc.creating_file
make_bilets.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]

rows_num = libc.file
rows_num.argtypes = [ctypes.c_int, ctypes.c_int]


print("Select: \n1)Formation of examination tickets \n2)End the program")

answer = val_input()

while answer != 1 and answer != 2:

    print("There is no such task! Try again")

    answer = val_input()


while answer != 2:

    while True:

        total_amount = total()

        if total_amount == -1:
            raise FileNotFoundError("Unable to open file!")
                
            
        print("Enter amount of questions in 1 ticket: ")

        users_amount = val_input()
            

        print("\nTotal amount of questions: ",  total_amount)
            
        res = check(users_amount, total_amount)
       
        while res == 0:
            
            print("It is not possible to create tickets with so many questions, try again!")

            users_amount = val_input()
           
            res = check(users_amount, total_amount)
            
        amount_of_quest_in_one = users_amount
        tickets_amount = res

        rows = rows_num(tickets_amount, amount_of_quest_in_one)

        print("Amount of questions in ticket: ", amount_of_quest_in_one)
        print("Amount of tickets: ", tickets_amount)
                
        b = make_bilets(rows, tickets_amount, amount_of_quest_in_one)

        if b == -1:
            raise ArithmeticError("It is not possible to create tickets!")
        elif b == 00:
            raise RuntimeError("It is not possible to create tickets with so many questions!")

        else:
            print("\nExamination tickets created successfully")
            break

    print("\nEnter 2 to end the program, or 1 to recreate tickets or restart")

    answer = val_input()

    while answer != 1 and answer != 2: 

        print("There is no such task! Try again")

        answer = val_input()

print("The program is complete")