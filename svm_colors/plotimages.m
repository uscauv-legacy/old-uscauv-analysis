function [] = plotimages(positiveexamples, negativeexamples, trainingspace)

    figure; hold on;
    scatter3(positiveexamples(:,1), positiveexamples(:,2), positiveexamples(:,3), 'g');
    scatter3(negativeexamples(:,1), negativeexamples(:,2), negativeexamples(:,3), 'r');

    if trainingspace == 'hsvimage'
        title('HSV Encoding');
        xlabel('h');
        ylabel('s');
        zlabel('v');
    elseif trainingspace == 'labimage'
        title('Lab Encoding');
        xlabel('L');
        ylabel('a');
        zlabel('b');
    elseif trainingspace == 'rgbimage'
        title('RGB Encoding');
        xlabel('R');
        ylabel('G');
        zlabel('B');
    end

end