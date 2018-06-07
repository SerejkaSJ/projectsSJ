
function calculator(str)
	print("Enter: "..str)
	local size = string.len(str)
	local en = string.sub(str, size,size)
	print("End: "..en)
	 if en == '-'  or en =='*' or en =='+' or en =='/' then
		print("ERROR")
		return str;
	 end
	str = str..'='
	 local expression = {}
		local numbuf = {}
	local chek = str:find('[%-,%*,%+,%/]')
	local size = string.len(str)
	if chek  then 
		str = str:gsub(' ','')
		print("str"..str)
		for i =1,size do
			local chr = str:sub(i,i)
			if chr:find('[0-9%.]') then
				print(chr)
				numbuf[#numbuf+1] = chr
				
			elseif #numbuf > 0 then
              print('elseif')
				expression[#expression+1] = table.concat(numbuf)
				numbuf={}
				expression[#expression+1] = chr
			else
			print('else')
				expression[#expression+1] = chr
			end
			
		end
	else
		print 'bad'
		return str:sub(1,size-1)
	end
	if 	   expression[2] == '+' then
		return tonumber(expression[1]) + tonumber(expression[3])
	elseif expression[2] == '-' then
		return tonumber(expression[1]) - tonumber(expression[3])
	elseif expression[2] == '/' then
		return tonumber(expression[1]) / tonumber(expression[3])
	elseif expression[2] == '*' then
		return tonumber(expression[1]) / tonumber(expression[3])
	end
end
local str = io.read()
local answer = calculator(str)
---return answer
print("Answer: "..answer)