SELECT Id, ShipCountry,case
									WHEN ShipCountry IN( 'USA','Mexico','Canada') 
									THEN 'NorthAmerica'
									ELSE 'OtherPlace' 
									END
FROM "Order"
WHERE Id >= 15445
ORDER BY  Id
LIMIT 20;
