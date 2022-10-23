--Q7_TOTAL_COST_QUARTILES
--zjh
SELECT CompanyName,CustomerId,TotalExpenditures
FROM (SELECT*, ntile(4) OVER(ORDER BY TotalExpenditures) AS result
			FROM (SELECT ifnull(CompanyName, 'MISSING_NAME') AS CompanyName, 
																		CustomerId, round(sum(UnitPrice*Quantity),2) AS TotalExpenditures
            FROM 'Order' join OrderDetail on OrderDetail.OrderId='Order'.Id
                       left join Customer on 'Order'.CustomerId=Customer.Id
            GROUP BY CustomerId))
WHERE result=1
ORDER BY TotalExpenditures;