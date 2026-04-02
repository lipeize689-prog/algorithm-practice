# Problem Description

There are \( n \) people and \( m \) directed way for them to send message to others with cost \( C \). We need to find a manager among these \( n \) people whose message can be sent to all \( n \) people with at least a way and the minimum cost. Additionally, each person wants to know who is responsible for sending message to him.

## Input Format

The first line contains two integers \( n \) and \( m \). Note that the people are numbered from 0 to \( n - 1 \).

For the following \( m \) lines, each line contains three integers \( s \), \( t \) and \( C \), meaning that person \( s \) could send message to person \( t \) with cost \( C \).

## Output Format

If no such person can be chosen as a manager, output "impossible".

Otherwise, print the minimum cost and the number of manager. If there exists multiple satisfied managers, choose the one with the minimum number. Then, for the next \( n \) lines, for each person \( i \), output which person would send him message. The format should be the person \( i \) followed by a space and the person \( j \) who sends message to the person \( i \). If the person \( i \) is the manager, you should output only \( i \).

---

# 输入数据 1

4 4  
0 1 10  
0 2 10  
1 3 20  
2 3 30  

# 输出数据 1

40 0  
0  
1 0  
2 0  
3 1  

---

# 输入数据 2

7 15  
0 1 9  
3 0 3  
0 4 5  
1 2 3  
2 1 7  
1 3 9  
4 3 4  
5 4 3  
3 2 8  
3 5 5  
2 5 9  
2 6 6  
6 2 4  
5 6 4  
6 5 8  

# 输出数据 2

25 5  
0 3  
1 2  
2 6  
3 4  
4 5  
5  
6 5  

---

**Hint**

For \( 100\% \) of the testcases, \( $1 \leq n \leq 10^3, 1 \leq m \leq 10^4, 1 \leq C \leq 1000$ \).