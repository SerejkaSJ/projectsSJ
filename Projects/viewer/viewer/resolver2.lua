local helper = require"helper"
log = helper.log
function elements(pathFile)
	helper.log("pathFile: "..pathFile)
	local Elements = {}
	Elements.count = {}

	local subckt, main = ReadFile(pathFile)

	Elements = ProcessingMain(main,Elements)
	--ProcessingSubckt(Elements)
	
	return Elements
end


function ProcessingMain(main,Elements)
	local mainTab = main:split("\n") 
	local Transistors= findTransistors(mainTab)
	local tranWorked = table.copy(Transistors)
	local Invertors, tranWorked = findInvertors(tranWorked)
	local InvertorWorked = table.copy(Invertors)
	local commonGate = findCommonGate(tranWorked)
	local NAND, commonGate, Invertors = findNand(commonGate, Invertors)
	local NOR, commonGate, Invertors = findNor(commonGate, Invertors)
	
	Elements.count = {
		transistors = #Transistors,
		invertors = #Invertors,
		nand2 = #NAND,
		nor2 = #NOR,
	}
	helper.log(#Transistors)
	Elements.transistors = Transistors
	Elements.invertors = Invertors
	Elements.nand2 = NAND
	Elements.nor2 = NOR
	
	return Elements
	
end

function findNor(commonGate, Invertors)
	local NOR = {}
	for i, inv in pairs(Invertors) do
		for j, common in pairs(commonGate) do
			local tab = {}
			if inv.vdd == common.P.drain and inv.vss == common.N.source then
				tab.items = {}
				tab.inA = inv.inA
				tab.inB = common.gate
				tab.out = inv.out
				tab.vdd = inv.vdd
				tab.vss = common.N.source
				tab.name = inv.name..common.name
				table.insert(tab.items, inv.items[1])
				table.insert(tab.items, inv.items[2])
				table.insert(tab.items, common.N.name)
				table.insert(tab.items, common.P.name)

				table.insert(NOR, tab)
				
				Invertors[i] = nil
				commonGate[j] = nil
			end
		end
	end
	return NOR, commonGate, Invertors
end

function findNand(commonGate, Invertors)
	local NAND = {}
	for i, inv in pairs(Invertors) do
		for j, common in pairs(commonGate) do
			local tab = {}
			if inv.vss == common.N.drain and inv.vdd == common.P.source then
				tab.items = {}
				tab.inA = inv.inA
				tab.inB = common.gate
				tab.out = inv.out
				tab.vdd = inv.vdd
				tab.vss = common.N.source
				tab.name = inv.name..common.name
				table.insert(tab.items, inv.items[1])
				table.insert(tab.items, inv.items[2])
				table.insert(tab.items, common.N.name)
				table.insert(tab.items, common.P.name)

				table.insert(NAND, tab)
				Invertors[i] = nil
				commonGate[j] = nil
			end
		end
	end
	return NAND, commonGate, Invertors
end

function findCommonGate(Transistors)
	local common = {}
	for i,ver in pairs(Transistors) do
		local f = false
		for j, val in pairs(Transistors) do
			repeat
			local tab = {}
			if i == j then break end
			if ver.type == "P" and val.type == "N" and ver.gate == val.gate  then
				tab.N = val
				tab.P = ver
				tab.gate  = ver.gate
				tab.name  = ver.name..val.name
				
				table.insert(common, tab)
				Transistors[i] = nil
				Transistors[j] = nil
				f = true
				break
			end
			until true
			if f then break end
		end
	end
	log("count common "..#common)
	return common

end
function findInvertors(Transistors)
	local Invertor = {}
	local del = {}
	for i,ver in pairs(Transistors) do
		for j, val in pairs(Transistors) do
			repeat
			local inv = {}
			if i == j then break end
			if ver.type == "P" and val.type == "N" and ver.drain == val.drain and ver.gate == val.gate  then
				inv.items = {}
				inv.name  = ver.name..val.name
				inv.inA   = ver.gate
				inv.vdd   = ver.source
				inv.vss   = val.source
				inv.out   = ver.drain
			
				table.insert(inv.items, val.name)
				table.insert(inv.items, ver.name)
				
				table.insert(Invertor,inv)
				table.insert(del, i)
				table.insert(del, j)
			end
			until true
		end
	end
	log("count invertors "..#Invertor)
	table.sort(del, function(a, b) return a>b end)
	for _, n in ipairs(del) do
		table.remove(Transistors, n)
	end
	return Invertor, Transistors
end

function findTransistors(main)
	local Transistor = {}
	for i, line in ipairs(main) do
		print(line)
		if not line:match('^M?%d+') then break	end

			local tab = {}
			local str = string.split(line," ")
			tab.name 	  = str[1]
			tab.drain 	  = str[2]
			tab.gate 	  = str[3]
			tab.source 	  = str[4]
			tab.substrate = str[5]
			tab.type 	  = str[6]
			table.insert(Transistor,tab)
	end
	log("count transistor: "..#Transistor)
	return Transistor, #Transistor
end


function ReadFile(pathFile)

	local file = io.open(pathFile)
	local main = file:read('*a')

	local subckt ={}
	for block in main:gmatch([[^%.SUBCKT(.-)%END]]) do
		table.insert(subckt, block)
		if block:len() > 3 then
			main:gsub(block, "")
		end
	end

	return subckt, main
end