%diff two graph

function diff_graph(graph1,graph2)

    data1 = graph1.Data;
    data2 = graph2.Data;
    graph1size = size(data1);
    graph2size = size(data2);
    
    time = graph1.Time;
    
    if graph1size ~= graph2size
        exit(1);
    end
    
    count = 0;
    match = 0;
    
    if graph1size(1) > 1
        for i=1:graph1size(2) %horizontal
            for j=1:graph1size(1) %vertical
                array_num = j + (i - 1) * graph1size(2);
                gerror = data1(array_num)-data2(array_num);
                if gerror == 0
                    match = match + 1;
                end
                count = count + 1;
            end
        end
    end
    
    gosa = 0;
    if graph1size(1) > 1
        for i=1:graph1size(2) %horizontal
            for j=2:graph1size(1) %vertical
                array_num = j + (i - 1) * graph1size(2);
                data1_cntr = (data1(array_num) + data1(array_num - 1))/2;
                data2_cntr = (data2(array_num) + data2(array_num - 1))/2;
                hensa = data1_cntr - data2_cntr;
                hensa = hensa * hensa;
                gosa = gosa + hensa * (time(j) - time(j-1));
            end
        end
    end
    disp('match');
    disp(match);
    disp(match/count);
    disp('square error');
    disp(gosa);
end
            