function exist_files(sys)

if exist('result_state.csv','file') ~= 2  
    delete('result_state.csv');
elseif exist('result_out.csv','file') ~= 2
    delete('result_out.csv');
end

statesys = sprintf('state_%s',sys);
outsys = sprintf('out_%s',sys);

close_system(statesys,0);
close_system(outsys,0);

if exist(statesys,'file') == 4
    delete(statesys);
    disp('delete state model')
end
if exist(outsys,'file') == 4
    delete(outsys);
    disp('delete out model');
end