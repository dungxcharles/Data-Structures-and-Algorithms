# Polynomial Manipulation
**Description:** A polynomial is stored in a linked list:
* Each term is stored in a node of the list with 2 fields: coefficient and exponent
* Nodes are always sorted in a decreasing order of exponents
* No two nodes have the same value of exponents

Each polynomial has an identifier which is a positive integer from 1 to 10000

**Given a list of commands over polynomials below:**
* Create <poly_id>: create a polynomial with identifier <pol_id> if this polynomial does not exists, otherwise, do nothing

* AddTerm <poly_id> <coef> <exp>: Add a term with coefficient <coef> and exponent <exp> to the polynomial having identifier <poly_id> (create a new polynomial if it does not exist)

* EvaluatePoly <poly_id> <variable_value>: Evaluate and print the value of the polynomial having identifier <poly_id> and <variable_value> is the value of the variable (print 0 if the polynomial does not exist) 

* AddPoly <poly_id1> <poly_id2> <result_poly_id>: Perform the addition operation over two polynomials <pol_id1> and <poly_id2>. The resulting polynomial will have identifier <result_poly_id> (if the polynomial <result_poly_id> exists, then overrides the existing polynomial)

* PrintPoly <poly_id>: print the polynomial <poly_id> (if it exists) to stdout under the form <c_1> <e_1> <c_2> <e_2> ... (sequence of pairs of (coefficient, exponent) of terms of the polynomial in a decreasing order of exponents)

* Destroy <poly_id>: destroy the polynomial having identifier <poly_id>

#### **Input**
Each line contains a command described above (terminated by a line containing *)

#### **Output**

#### **Example**
**Input**
```
AddTerm 1 3 2
AddTerm 1 4 0
AddTerm 1 6 2
AddTerm 2 3 2
AddTerm 2 7 5
PrintPoly 1
PrintPoly 2
AddPoly 2 1 3
PrintPoly 3
EvaluatePoly 2 1
*
```
**Output**
```
9 2 4 0
7 5 3 2
7 5 12 2 4 0
10 
```
