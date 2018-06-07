function elements(pathFile)
	print("in lua: "..pathFile)
	local Elements = {}
	Elements.count = {}
	count = Elements.count
	--local pathFile = [[c:\lua\test.sp]]
	local TransistorTable, TransistorCount = findTransistor(pathFile)
	local InvertorTable, InvertorCount 	   = findInvertor(TransistorTable)
	local NAND2Table, NAND2Count, delNAND  = findNAND2(TransistorTable, InvertorTable)
	table.sort(delNAND,function (a, b) return (a > b) end)
	for i, v in pairs(delNAND) do
		table.remove(InvertorTable,v)
	end
	local NOR2Table, NOR2Count,delNor	   = findNOR2(TransistorTable, InvertorTable)
	for i, v in pairs(delNor) do
		table.remove(InvertorTable,v)
	end
	count.transistors	 = TransistorCount
	count.invertors 	 = #InvertorTable
	count.nand2 		 = NAND2Count
	count.nor2 			 = NOR2Count
	Elements.transistors = TransistorTable
	Elements.invertors   = InvertorTable
	Elements.nand2 		 = NAND2Table
	Elements.nor2 		 = NOR2Table
	-- for i ,val in pairs(Elements) do
		-- print(i)
	-- end
	return Elements
end


function string:split(delimiter)
  local result = { }
  local from  = 1
  local delim_from, delim_to = string.find( self, delimiter, from  )
  while delim_from do
    table.insert( result, string.sub( self, from , delim_from-1 ) )
    from  = delim_to + 1
    delim_from, delim_to = string.find( self, delimiter, from  )
  end
  table.insert( result, string.sub( self, from  ) )
  return result
end

function findTransistor(pathFile)
print("in lua: FindTransistor()"..pathFile)
	local Transistor={}
	for line in io.lines(pathFile) do
		local tab = {}
		if line:match('^M%d+') then
			local str = string.split(line," ")
			tab.name 	  = str[1]
			tab.drain 	  = str[2]
			tab.gate 	  = str[3]
			tab.source 	  = str[4]
			tab.substrate = str[5]
			tab.type 	  = str[6]
			table.insert(Transistor,tab)
		end
	end
	return Transistor, #Transistor
end

function findInvertor(Table)
print("in lua: FindInventor()")
	local Invertor = {}
	for i,ver in ipairs(Table) do
		for j, val in pairs(Table) do
			repeat
			local inv = {}
			if i == j then break end
			if ver.type == "P" and val.type == "N" and ver.drain == val.source and ver.gate == val.gate  then
				inv.items = {}
				inv.name  = ver.name..val.name
				inv.inA   = ver.gate
				inv.vdd   = ver.source
				inv.vss   = val.drain
				inv.out   = ver.drain
			
				table.insert(inv.items, val.name)
				table.insert(inv.items, ver.name)
				
				table.insert(Invertor,inv)
			end
			until true
		end
	end
		return Invertor, #Invertor 
end

function findNAND2(Transistors, Invertors)
print("in lua: FindNand2()")
	local Nand,Nand2, del, delete = {}, {}, {}, {}
	for i, inv in ipairs(Invertors) do
		for j, tran in ipairs(Transistors) do
			local nand = {}
			if tran.type == "N" and tran.source == inv.vss then
				nand.tran = tran.name
				nand.tran = tran
				nand.inv  = inv.name
				nand.inv  = inv
				table.insert(Nand,nand)
				table.insert(del,i)
			end
		end
	end
	for i, val in ipairs(Nand) do
		for j, tr in ipairs(Transistors) do
			local nand = {}
			if tr.type == "P" and tr.gate == val.tran.gate and tr.drain == val.inv.out  and tr.source == val.inv.vdd then
				nand.items = {}
				nand.inA   = tr.gate
				nand.inB   = val.inv.inA
				nand.out   = val.inv.out
				nand.vdd   = val.inv.vdd
				nand.vss   = val.tran.drain
				nand.name  = val.inv.name..tr.name..val.tran.name
				table.insert(nand.items, tr.name)
				table.insert(nand.items, val.tran.name)
				table.insert(nand.items, val.inv.items[1])
				table.insert(nand.items, val.inv.items[2])
				table.insert(Nand2,nand)
				table.insert(delete,del[i])
			end
		end
	end
	return Nand2, #Nand2, delete
end

function findNOR2(Transistors, Invertors)
print("in lua: FindNor2()")
	local Nor,Nor2, del, delete = {}, {}, {}, {}
	for i, inv in ipairs(Invertors) do
		for j, tran in ipairs(Transistors) do
			local nor = {}
			if tran.type == "P" and tran.drain == inv.vdd then
				nor.tran = tran.name
				nor.tran = tran
				nor.inv  = inv.name
				nor.inv  = inv
				table.insert(Nor,nor)
				table.insert(del,i)
			end
		end
	end
	for i, val in ipairs(Nor) do
		for j, tr in ipairs(Transistors) do
			local nor = {}
			if tr.type == "N" and tr.gate == val.tran.gate and tr.source == val.inv.out and tr.drain == val.inv.vss then
				nor.items = {}
				nor.inA  = tr.gate
				nor.inB  = val.inv.inA
				nor.out  = val.inv.out
				nor.vss  = val.inv.vss
				nor.vdd  = val.tran.source
				nor.name = val.inv.name..tr.name..val.tran.name
				table.insert(nor.items, tr.name)
				table.insert(nor.items, val.tran.name)
				table.insert(nor.items, val.inv.items[1])
				table.insert(nor.items, val.inv.items[2])
				table.insert(Nor2,nor)
				table.insert(delete,del[i])
			end
		end
	end
	return Nor2, #Nor2, delete
end
