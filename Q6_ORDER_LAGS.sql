SELECT Id, OrderDate, PreviousOrderDate, ROUND((julianday(OrderDate) - julianday(PreviousOrderDate)),2) AS Difference
FROM (SELECT Id,CustomerId,OrderDate,lag(OrderDate,1,OrderDate) OVER(ORDER BY OrderDate) AS PreviousOrderDate
      FROM 'Order'
      WHERE CustomerId = 'BLONP')
ORDER BY OrderDate 
LIMIT 10;