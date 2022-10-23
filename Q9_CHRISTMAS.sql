WITH ProductName AS (SELECT DISTINCT ProductName
										 FROM 'Order'
                       JOIN Product ON Product.Id=OrderDetail.ProductId
										   JOIN OrderDetail ON OrderDetail.OrderId='Order'.Id
                       JOIN Customer ON Customer.Id='Order'.CustomerId
										 
                     WHERE CompanyName='Queen Cozinha' AND OrderDate LIKE '2014-12-25%'
										 
                     ORDER BY Product.Id)

SELECT group_concat(ProductName) AS string FROM ProductName;