import sys

print 'Argument List:', str(sys.argv)

file = open(sys.argv[1], "r")
out = open(sys.argv[2], "a+", buffering=0)
lines = file.readlines()
x = 0

out.write("PrimeA, PrimeB\n")

for lineA in lines:
    for lineB in lines:
        if int(lineA) == int(lineB) + 2:
            print(str(x) + " Twinprimes found! " + str(int(lineB)) + " " + str(int(lineA)))
            x += 1
            out.write(str(int(lineB)) + ", " + str(int(lineA)) + "\n")
            break
