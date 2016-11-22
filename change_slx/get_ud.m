function get_ud(sys)

sysH = load_system(sys);
allblkList = find_system(sysH,'FindAll','On','type','block','blocktype','UnitDelay');

num = size(allblkList);
blklist = zeros(num(1),1);
disp(blklist);
disp(allblkList);
for i=1:num(1)
    disp(get_param(allblkList(i),'name'));
    blklist(i) = get_param(allblkList(i),'name');
end;

disp(blklist);



