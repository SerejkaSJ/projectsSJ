local tab = {}

tab["&#1040"] = "А"	
tab["&#1041"] = "Б"	
tab["&#1042"] = "В"	
tab["&#1043"] = "Г"	
tab["&#1044"] = "Д"	
tab["&#1045"] = "Е"	
tab["&#1046"] = "Ж"	
tab["&#1047"] = "З"	
tab["&#1048"] = "И"	
tab["&#1049"] = "Й"	
tab["&#1050"] = "К"	
tab["&#1051"] = "Л"	
tab["&#1052"] = "М"	
tab["&#1053"] = "Н"	
tab["&#1054"] = "О"	
tab["&#1055"] = "П"	
tab["&#1056"] = "Р"	
tab["&#1057"] = "С"	
tab["&#1058"] = "Т"	
tab["&#1059"] = "У"	
tab["&#1060"] = "Ф"	
tab["&#1061"] = "Х"	
tab["&#1062"] = "Ц"	
tab["&#1063"] = "Ч"	
tab["&#1064"] = "Ш"	
tab["&#1065"] = "Щ"	
tab["&#1066"] = "Ъ"	
tab["&#1067"] = "Ы"	
tab["&#1068"] = "Ь"	
tab["&#1069"] = "Э"	
tab["&#1070"] = "Ю"	
tab["&#1071"] = "Я"	
tab["&#1072"] = "а"	
tab["&#1073"] = "б"	
tab["&#1074"] = "в"	
tab["&#1075"] = "г"	
tab["&#1076"] = "д"	
tab["&#1077"] = "е"	
tab["&#1078"] = "ж"	
tab["&#1079"] = "з"	
tab["&#1080"] = "и"	
tab["&#1081"] = "й"	
tab["&#1082"] = "к"	
tab["&#1083"] = "л"	
tab["&#1084"] = "м"	
tab["&#1085"] = "н"	
tab["&#1086"] = "о"	
tab["&#1087"] = "п"	
tab["&#1088"] = "р"	
tab["&#1089"] = "с"	
tab["&#1090"] = "т"	
tab["&#1091"] = "у"	
tab["&#1092"] = "ф"	
tab["&#1093"] = "х"	
tab["&#1094"] = "ц"	
tab["&#1095"] = "ч"	
tab["&#1096"] = "ш"	
tab["&#1097"] = "щ"	
tab["&#1098"] = "ъ"	
tab["&#1099"] = "ы"	
tab["&#1100"] = "ь"	
tab["&#1101"] = "э"	
tab["&#1102"] = "ю"	
tab["&#1103"] = "я"		
tab["&#1025"] = "ё"

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


function decode(code)
	local answer = ""
	if not code or code == "" then return answer end
	local codeTab = string.split(code, ";")
	for _,symbol in ipairs(codeTab) do
		print(symbol)
		answer = answer..tab[symbol]
	end
	return answer
end

print(decode("&#1075;.&#1056;&#1086;&#1089;&#1090;&#1086;&#1074;-&#1085;&#1072;-&#1044;&#1086;&#1085;&#1091;"))
