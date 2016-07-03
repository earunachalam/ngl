function [ME, filename] = cppplot(varargin)


    dirs = dir('/home/easun/Desktop/Conway6/data');
    filename = dirs(size(dirs,1)).name;
    doi = ['/home/easun/Desktop/Conway6/data/' filename]; %directory of interest

    first = 0;
    last = (numel(dir([doi '/physical_state/'])) - 4)/2; % the four items that are not counted at . , .. , 0_1, and 0_2
    parameters = tdfread([doi '/cfg/parameters.txt']);
    gridDim_orig = parameters.x1(2);

    if nargin == 3
        first = varargin{1};
        last = varargin{2};
        gridDim_orig = varargin{3};
    elseif nargin == 2
        first = varargin{1};
        last = varargin{2};
        % parameters = tdfread([doi '/cfg/parameters.txt']);
        % gridDim_orig = parameters.x1(2);
    end


    parfor timestep = first:last %realmax int

        filename_sp1 = [doi '/physical_state/' num2str(timestep) '_1.csv']; file1_info = dir(filename_sp1);
        filename_sp2 = [doi '/physical_state/' num2str(timestep) '_2.csv']; file2_info = dir(filename_sp2);


        if file1_info.bytes() ~= 0
            coords_sp1 = csvread(filename_sp1);
            %adjust coordinates to MATLAB convention to get appropriate x-y plot
            tempcol = coords_sp1(:,1); coords_sp1(:,1) = coords_sp1(:,2); coords_sp1(:,2) = tempcol;
            coords_sp1(:,1) = gridDim_orig - coords_sp1(:,1);

            % if any(any(coords_sp1(:,1:2) > gridDim_orig))||any(any(coords_sp1(:,1:2) < 0))
            % 	disp('invalid coordinates: dynamic species');
            % 	disp(doi); return;
            % end
        else
            coords_sp1 = [];
        end

        if file2_info.bytes() ~= 0
            coords_sp2 = csvread(filename_sp2);
            %adjust coordinates to MATLAB convention to get appropriate x-y plot
            tempcol = coords_sp2(:,1); coords_sp2(:,1) = coords_sp2(:,2); coords_sp2(:,2) = tempcol;
            coords_sp2(:,1) = gridDim_orig - coords_sp2(:,1);

            % if any(any(coords_sp2(:,1:2) > gridDim_orig))||any(any(coords_sp2(:,1:2) < 0))
            % 	disp('invalid coordinates: static species');
            % 	disp(doi); return;
            % end
        else
            coords_sp2 = [];
        end

        %render the simulation box
        fsrender(5, false, timestep, coords_sp1, coords_sp2, gridDim_orig, gridDim_orig, [doi '/img']);
        disp(['Frame ' num2str(timestep) ': render complete.']);
    end

    disp([doi '/img/0.png']);

end
