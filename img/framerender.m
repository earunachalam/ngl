function framerender( scaling, timestep, cellProp, gridDimI_orig, gridDimJ_orig, directory, map )
% FRAMERENDER Generate image of simulation box at given timestep
%   FRAMERENDER returns a PNG image of the simulation box at a given
%   timestep. Three input arguments are required: the first is an nx3xt
%   cell array containing the positions and energies of n SP1 objects over
%   t timesteps; the second is an nx3xt cell array containing the positions
%   and energies of n SP2 objects over t timesteps; and the third is a
%   double giving the number of timesteps. 'F' indicates that this is the
%   fast variant of the render function that employs a restricted domain
%   comparison for shading. 'S' indicates that this variant of the render
%   function can scale image size to produce arbitrarily smooth curves.

gridDimI = gridDimI_orig * scaling;
gridDimJ = gridDimJ_orig * scaling;
filename = [directory '/'];

% Create array for matrix (for eventual export as PNG image)
raw_out = 0 * ones(gridDimI,gridDimJ); % black

if isempty( cellProp ), return; end

% Extract parameters from input
iCoord = round(scaling .* cellProp(:,5));
iCoord( iCoord == 0 ) = gridDimI;

jCoord = round(scaling .* cellProp(:,6));
jCoord( jCoord == 0 ) = gridDimJ;

% check validity of all coordinates
[iCoord, jCoord] = checkCoords(iCoord, jCoord, gridDimI, gridDimJ);

% calculate cell radius for display
cR = scaling .* cellProp(:,3); cRInt = round(cR);

for cellNum = 1:numel(iCoord) % for each cell

    objColor = 255 - 110*cellProp(cellNum,1);
%     switch cellProp(cellNum,1) % Color SP1 blue, SP2 red
%         case 1 % SP1
%             objColor = 3; % blue (layer 3 in RGB)
%         case 2 % SP2
%             objColor = 1; % red (layer 1 in RGB)
%     end % switch SP

    iPseudo = NaN; jPseudo = NaN; modified = cellProp(cellNum, 4); if modified, display('Modification has occurred'); end

    % fill all pixels determined to be contained without adjustment
    % for periodic boundary conditions
    raw_out = pixelFill( iCoord(cellNum), jCoord(cellNum), cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );

    % fill pixels determined to be contained as a result of
    % periodic boundary conditions

    if abs( gridDimI - iCoord(cellNum) ) < cR(cellNum) % too close to top
        % create artificial center outside simulation box and fill from this point
        iPseudo = iCoord(cellNum) - gridDimI;
        raw_out = pixelFill( iPseudo, jCoord(cellNum), cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );
    end % if too close to bottom

    if abs( gridDimJ - jCoord(cellNum) ) < cR(cellNum) % too close to right
        % create artificial center outside simulation box and fill from this point
        jPseudo = jCoord(cellNum) - gridDimJ;
        raw_out = pixelFill( iCoord(cellNum), jPseudo, cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );
    end % if too close to right

    if abs( iCoord(cellNum) ) < cR(cellNum) % too close to bottom
        % create artificial center outside simulation box and fill from this point
        iPseudo = gridDimI + iCoord(cellNum);
        raw_out = pixelFill( iPseudo, jCoord(cellNum), cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );
    end % if too close to top

    if abs( jCoord(cellNum) ) < cR(cellNum) % too close to left
        % create artificial center outside simulation box and fill from this point
        jPseudo = gridDimJ + jCoord(cellNum);
        raw_out = pixelFill( iCoord(cellNum), jPseudo, cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );
    end % if too close to left

    if ~isnan(iPseudo) && ~isnan(jPseudo)
        % if a center has been created previously along the i
        % axis as well as the j-axis, then we may infer that
        % the cell is too close to both axes and is therefore
        % too close to a corner; consequently, a portion of the
        % cell must appear in the opposite corner
        raw_out = pixelFill( iPseudo, jPseudo, cRInt(cellNum), raw_out, objColor, gridDimI, gridDimJ, modified );
    end

end % for cellNum

clear cR; clear cRInt;

imwrite(raw_out, eval(map), [filename num2str(timestep) '.png']);
    
end % function render

function [ raw_out ] = pixelFill( iPos, jPos, radius, raw_out, objColor, gridDimI, gridDimJ, modified )
% PIXELFILL Fill pixels within specified distance of given point
%   Given a point with coordinates iPos and jPos (along i- and j-axes,
%   respectively), determine the coordinates of all points with 

jlist = (jPos - radius - 1):(jPos + radius + 1); 
ilist = (iPos - radius - 1):(iPos + radius + 1);
coord1 = (repmat( ilist', 1, numel(jlist) )); %I coordinate
coord2 = (repmat( jlist, numel(ilist), 1 )); %J coordinate
coord3 = (repmat( ilist', 1, numel(jlist) )) - iPos; %I distance
coord4 = (repmat( jlist, numel(ilist), 1 )) - jPos; %J distance
distEucl = sqrt( coord3.^2 + coord4.^2 ); %Euclidean distance

distEucl(logical(repmat(((coord1 < 1) + (coord1 > gridDimI) + (coord2 < 1) + (coord2 > gridDimJ)), 1, 1))) = Inf;

% calculate indices of contained pixels
[contPixels_i, contPixels_j] = find(distEucl <= radius);

for numPixel = 1:numel(contPixels_i)
    raw_out(iPos - radius - 2 + contPixels_i(numPixel), jPos - radius - 2 + contPixels_j(numPixel)) = objColor; % 222 colorcube green
end % for numPixel

% if modified
%     for numPixel = 1:numel(contPixels_i)
%         raw_out(iPos - radius - 2 + contPixels_i(numPixel), jPos - radius - 2 + contPixels_j(numPixel)) = 255; % 222 colorcube green
%     end % for numPixel
% else %not modified
%     for numPixel = 1:numel(contPixels_i)
%         if objColor == 3
%         	raw_out(iPos - radius - 2 + contPixels_i(numPixel), jPos - radius - 2 + contPixels_j(numPixel)) = 100; %237 colorcube blue
%         else
%         	raw_out(iPos - radius - 2 + contPixels_i(numPixel), jPos - radius - 2 + contPixels_j(numPixel)) = 150; %209 colorcube red
%         end
%     end % for numPixel
% end

end % function pixelFill

function [iCoord, jCoord] = checkCoords(iCoord, jCoord, gridDimI, gridDimJ)

if any(iCoord < 0) || any(iCoord > gridDimI) || any(jCoord < 0) || any(jCoord > gridDimJ)
    
    display(['i: ' num2str(iCoord(logical((any(iCoord < 0) + any(iCoord > gridDimI) + any(jCoord < 0) + any(jCoord > gridDimJ))>0)))]);
    display(['j: ' num2str(jCoord(logical((any(iCoord < 0) + any(iCoord > gridDimI) + any(jCoord < 0) + any(jCoord > gridDimJ))>0)))]);
    display('Error in framerender'); %display(timestep); display(errorObj .* (1:numel(errorObj))');
    display('Invalid coordinates: return to invoking function moveGen')
    display(iCoord); display(jCoord);
    invalid = (iCoord < 0) + (iCoord > gridDimI) + (jCoord < 0) + (jCoord > gridDimJ);
    remainingValid = ~invalid;

    iCoord = iCoord(remainingValid); jCoord = jCoord(remainingValid);

end

end