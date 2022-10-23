SELECT ProductName, CompanyName, ContactName
FROM (SELECT CustomerId, ProductId, ProductName, MIN(OrderDate)
		  FROM OrderDetail ordet
	        JOIN Product pd ON pd.Id = ordet.ProductId
	        JOIN "Order" od ON od.Id = ordet.OrderId
	    WHERE pd.Discontinued = 1
	    GROUP BY ProductId ) A

JOIN Customer c ON A.CustomerId = c.Id 

ORDER BY ProductName;
