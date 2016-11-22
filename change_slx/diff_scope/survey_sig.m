function survey_sig(data)

datasize = size(data);

for i=1:datasize(1)-1
    if data(i+1) ~= data(i)
        disp(i+1)
    end
end