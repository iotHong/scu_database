SELECT RegionDescription AS Region, FirstName, LastName, max(BirthDate) AS BirthDate
FROM Employee JOIN EmployeeTerritory ON Employee.Id=EmployeeTerritory.EmployeeId
              JOIN Territory ON EmployeeTerritory.TerritoryId=Territory.Id
	      JOIN Region ON Region.Id=Territory.RegionId
GROUP BY Region.Id
ORDER BY Region.Id;
