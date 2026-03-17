# Exercise 1.11
# how would you test the word count program? what kinds
# of input are most likely to uncover bugs if there are 
# any?

# strategy: test edge cases around word boundaries
# by stessing word logic (c == ' ' || c == '\n' || c == '\t')

# 1.11.1 basic test
echo "\nTest 1.11.1:"
echo "hello world" | ./example_01-05-04.out

# 1.11.2 multiple spaces
echo "\nTest 1.11.2:"
echo "hello    world" | ./example_01-05-04.out

# 1.11.3 leading + trailing spaces
echo "\nTest 1.11.3:"
echo "   hello world   " | ./example_01-05-04.out

# 1.11.4 only whitespaces
echo "\nTest 1.11.4:"
echo "     " | ./example_01-05-04.out

# 1.11.5 tabs, new lines and mixed whitespace
echo "\nTest 1.11.5:"
echo "hello\tworld\t\t  \nhello\n\tworld" | ./example_01-05-04.out

# 1.11.6 single character
echo "\nTest 1.11.6"
echo "a" | ./example_01-05-04.out

# 1.11.7 no traillling newline (echo adds \n)
echo "\nTest 1.11.7"
printf "hello world" | ./example_01-05-04.out
