%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% sys:入力の.slx
% beforedatafolder:モデル変更前のデータ群
% afterdatafolder:モデル変更後のデータ群

function checkfrequencyresponse(sys,beforedatafolder,afterdatafolder)
    
    %load_system(sys);
    
    %ファイルの順番は同じである前提
    beforefolder = sprintf('%s/*.mat',beforedatafolder);
    afterfolder = sprintf('%s/*.mat',afterdatafolder);
    beforedatalist = dir(beforefolder);
    afterdatalist = dir(afterfolder);
    
    input = frest.createFixedTsSinestream(0.1);
    
    for i = 1:size(beforedatalist,1)
        beforefile = beforedatalist(i).name;
        afterfile = afterdatalist(i).name;
        beforefile = sprintf('%s/%s',beforedatafolder,beforefile);
        afterfile = sprintf('%s/%s',afterdatafolder,afterfile);
        beforedata = matfile(beforefile);
        afterdata = matfile(afterfile);
        beforefrequencyresponse = beforedata.sysest;
        afterfrequencyresponse = afterdata.sysest; 
        aftersimout = afterdata.simout;
        if isequal(beforefrequencyresponse,afterfrequencyresponse)
        %if 0
            %disp(beforefile);
            disp('not change');
        else
            disp(beforefile);
            disp(afterfile);
            [pathstr,name,ext] = fileparts(beforefile);
            outputfile = sprintf('%s.fig',name);
            bodeplot(beforefrequencyresponse,afterfrequencyresponse);
            savefig(outputfile);
            %frest.simView(aftersimout,input,afterfrequencyresponse);
        end;
    end;
end
        