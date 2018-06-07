function delete(str)
print("worked")
	local lenght = string.len(str)
	print (lenght)
	str = string.sub(str,1,lenght-1)
	print(str)
	return str
end