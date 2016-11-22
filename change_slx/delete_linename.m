function delete_linename(sys)

sysH = load_system(sys);
linelist = find_system(sysH,'FindAll','On','LookUnderMasks','all','type','line');
line_num = size(linelist);
for i = 1:line_num(1)
    set_param(linelist(i),'name','');
end;