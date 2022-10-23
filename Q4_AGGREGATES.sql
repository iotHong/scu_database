SELECT categoryname, COUNT(*) as  Number, 
					round(avg(product.unitprice), 2) AS Avg,
					min(product.unitprice) AS Min, 
					max(product.unitprice) AS Max,
					sum(product.unitsonorder) AS TotalUnitsOnOrder
										
FROM product, category
WHERE category.id = product.categoryid 
GROUP BY categoryname
HAVING count(category.id) > 10
ORDER BY category.id;
