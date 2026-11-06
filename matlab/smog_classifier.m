% Image-based smog classification (offline, MATLAB R2022b+, Image Processing Toolbox)
% Source: FYDP report, Appendix A.1 (thresholds unchanged). Label 'Haze' matches the figures in the paper.
% Usage: set imgFile to a field image and run. Thresholds are empirical; adjust with test data.

imgFile = 'field_image.jpg';          % <-- your image
img = imread(imgFile);  img = im2double(img);

% Convert to grayscale and HSV
grayImg = rgb2gray(img);  hsvImg = rgb2hsv(img);

% === Feature extraction ===
brightness = mean(grayImg(:));                         % mean intensity
contrast   = std(grayImg(:));                          % standard deviation
saturation = mean(hsvImg(:, :, 2), 'all');             % mean saturation
laplacianFilter = fspecial('laplacian', 0.2);
laplacianImg = imfilter(grayImg, laplacianFilter, 'replicate');
sharpness = var(laplacianImg(:));                      % variance of Laplacian (focus measure)

% === Classification logic ===
if brightness < 0.4 && contrast < 0.1 && saturation < 0.5 && sharpness < 0.1
    airCondition = 'Heavy Smog';  labelColor = 'red';
elseif brightness < 0.6 && contrast < 0.3 && saturation < 0.4
    airCondition = 'Haze';        labelColor = 'yellow';   % called 'Foggy Weather' in the FYDP appendix
else
    airCondition = 'Clear';       labelColor = 'green';
end

% === Display with annotations ===
figure('Name', 'Air Quality Monitoring'); imshow(img);
title('Air Quality Monitoring Result'); hold on;
baseX = 30; baseY = 30; lineSpacing = 20;
text(baseX, baseY + 25  * lineSpacing, ['Brightness: ', num2str(brightness, '%.2f')], 'Color', 'white', 'FontSize', 10);
text(baseX, baseY + 50  * lineSpacing, ['Contrast: ',   num2str(contrast,   '%.2f')], 'Color', 'white', 'FontSize', 10);
text(baseX, baseY + 75  * lineSpacing, ['Saturation: ', num2str(saturation, '%.2f')], 'Color', 'white', 'FontSize', 10);
text(baseX, baseY + 100 * lineSpacing, ['Sharpness: ',  num2str(sharpness,  '%.4f')], 'Color', 'white', 'FontSize', 10);
plot(10, 200, 's', 'MarkerSize', 10, 'MarkerFaceColor', labelColor, 'MarkerEdgeColor', labelColor);
legend(airCondition, 'TextColor', labelColor, 'FontSize', 12, 'Location', 'southoutside');
hold off;
