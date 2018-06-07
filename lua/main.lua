t={}
i=3
t[1]=0;t[2]=1;
print(t[1],"\n",t[2])
while i<100 do
t[i]=t[i-2]+t[i-1];
print(t[i])
i=i+1;
	if i==15 then 
	break;
	end
end