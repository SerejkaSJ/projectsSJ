function delete(str)
	local lenght = string.len(str)
	print (lenght)
	str = string.sub(str,1,lenght-1)
	print(str)
end

local str = io.read()
local answer = delete(str)