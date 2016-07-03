% function cbrp(varargin)

% C++ Batch Read and Plot

    % colormap for rendering
    map = 'jet(255)';

    % location of all stored trajectories
    rootdir = '../data/';

    % get listing of all trajectories
    dirs = dir(rootdir);

    % get name of most recently created trajectories
    filename = dirs(size(dirs,1)).name;

    % directory of interest
    doi = [rootdir filename];

    % read parameter specification file
    parameters = csvread('../cfg/parameters.csv');

    % get half side length (in um) of the simulation box (extends from
    % -gridDim_orig to +gridDim_orig
    gridDim_orig = round(80*parameters(3));

    % default render goes from batch 0 to the highest batch number listed
    first = 0;
    last = (numel(dir([doi '/state/'])) - 3);% - 1;
    % the four items that are not counted at . , .. , 0, and the last
    % directory (presumably terminated halfway through with Ctrl-C, so not
    % complete)

    scaling = 5;
%     if nargin ~= 0
%         first = varargin{1};
%         last = varargin{2};
%     end

    nFramesPerBatch = parameters(2);

    parfor batch = first:last
        %     for batch = first:last
        % get name of current file
        filename = [doi '/state/' num2str(batch) '.csv']; file_info = dir(filename);

        if file_info.bytes() ~= 0

            coords = csvread(filename); coords = coords(:,1:10);
            display(['Coordinates from batch ' num2str(batch) ' imported.']);

            %adjust coordinates to MATLAB convention to get appropriate x-y plot
            coords(:,5:6) = coords(:,5:6) + gridDim_orig;
            tempcol = coords(:,5);
            coords(:,5) = coords(:,6);
            coords(:,6) = tempcol;
            coords(:,5) = 2*gridDim_orig - coords(:,5);
            coords(:,5:6) = 2*coords(:,5:6) - gridDim_orig;

            if batch == 0 % if trying to render frame for t = 0

                framerender(scaling, 0, coords(1:(end-1),:), 2*gridDim_orig, 2*gridDim_orig, [doi '/img'], map);

            else % if trying to render any other frame

                eofIndex = find(isnan(coords(:,1)));

                endIndex = -1; % row index to END read

                for frame = 1:min(nFramesPerBatch,numel(eofIndex))

                    startIndex = endIndex + 2;

                    endIndex = eofIndex(frame) - 1;

                    currFrameCoords = coords(startIndex:endIndex,:);
                    if isempty(currFrameCoords), break; end

                    timestep = (nFramesPerBatch*(batch - 1)) + frame;

                    %render the simulation box
                    framerender(scaling, timestep, currFrameCoords, 2*gridDim_orig, 2*gridDim_orig, [doi '/img'], map);
                end

            end

            disp(['Batch ' num2str(batch) ': render complete.']);

        else
            error(['Frame ' num2str(batch) ': no coordinates.']);
        end

        if batch == first, savCoord = coords; elseif batch==(first+1), savCoord2 = coords; end
    end

% end
