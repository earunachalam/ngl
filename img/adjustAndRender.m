%     for batch = first:last 
% get name of current file
filename = [doi '/state/' num2str(batch) '.csv']; file_info = dir(filename);        

if file_info.bytes() ~= 0

    coords = csvread(filename); coords = coords(:,1:10);% coords = sortrows(coords,2); coords(end-1,1) = 0;
    display(['Coordinates from batch ' num2str(batch) ' imported.']);

    %adjust coordinates to MATLAB convention to get appropriate x-y plot
    coords(:,5:6) = coords(:,5:6) + gridDim_orig;
    tempcol = coords(:,5);
    coords(:,5) = coords(:,6);
    coords(:,6) = tempcol;
    coords(:,5) = 2*gridDim_orig - coords(:,5);

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
