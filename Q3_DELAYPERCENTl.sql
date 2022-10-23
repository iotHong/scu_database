SELECT companyname, 
				ROUND(COUNT(CASE WHEN ShippedDate > RequiredDate THEN true ELSE NULL END) * 100.00/ count(*), 2) AS Percent
FROM 'Order', 'Shipper'
WHERE 'Order'.ShipVia = Shipper.id
GROUP BY Shipper.id
ORDER BY percent DESC
;
