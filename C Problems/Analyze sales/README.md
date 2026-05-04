# E-Commerce Sales Query System

## Problem Description
**This is a problem to deal with string and address in C (manually withou any built-in function) and to optimize code by appropriate Data structure and Algorithms**

You are given sales data from an e-commerce platform that manages multiple shops. Each order record contains information about a customer purchasing a product from a specific shop at a given time. Your task is to process this data and answer a series of queries efficiently.

---

## Input Format

The input consists of **two blocks**:

### Block 1 — Order Data

A sequence of lines, each representing one order in the following format:

```
<CustomerID> <ProductID> <Price> <ShopID> <TimePoint>
```

Terminated by a line containing only `#`.

### Block 2 — Query Block

A sequence of query lines (described below).

Terminated by a line containing only `#`.

---

## Field Specifications

| Field | Type | Constraints |
|---|---|---|
| `CustomerID` | String | Length 3–10 |
| `ProductID` | String | Length 3–10 |
| `Price` | Integer | 1 ≤ Price ≤ 1000 |
| `ShopID` | String | Length 3–10 |
| `TimePoint` | String | Format `HH:MM:SS` (e.g., `09:45:20`) |

---

## Query Types

| Query | Description |
|---|---|
| `?total_number_orders` | Return the total number of orders |
| `?total_revenue` | Return the total revenue across all shops |
| `?revenue_of_shop <ShopID>` | Return the total revenue of a specific shop |
| `?total_consume_of_customer_shop <CustomerID> <ShopID>` | Return the total amount spent by a customer at a specific shop |
| `?total_revenue_in_period <from_time> <to_time>` | Return the total revenue from orders placed in the time range `[from_time, to_time]` (inclusive) |

---

## Constraints

- Number of orders: up to **100,000**
- Number of queries: up to **100,000**
- All time points are within a single day (`00:00:00` – `23:59:59`)

---

## Output Format

For each query, print the result on a **separate line**.

---

## Example

### Input

```
C001 P001 10 SHOP001 10:30:10
C001 P002 30 SHOP001 12:30:10
C003 P001 40 SHOP002 10:15:20
C001 P001 80 SHOP002 08:40:10
C002 P001 130 SHOP001 10:30:10
C002 P001 160 SHOP003 11:30:20
#
?total_number_orders
?total_revenue
?revenue_of_shop SHOP001
?total_consume_of_customer_shop C001 SHOP001
?total_revenue_in_period 10:00:00 18:40:45
#
```

### Output

```
6
450
170
40
370
```

### Explanation

- **total_number_orders**: 6 orders total.
- **total_revenue**: 10 + 30 + 40 + 80 + 130 + 160 = 450.
- **revenue_of_shop SHOP001**: 10 + 30 + 130 = 170.
- **total_consume_of_customer_shop C001 SHOP001**: C001 bought from SHOP001 once for 10 and once for 30 → 40.
- **total_revenue_in_period 10:00:00 18:40:45**: Orders within the range are at 10:15:20 (40), 10:30:10 (10 + 130), 11:30:20 (160), 12:30:10 (30) → 370.