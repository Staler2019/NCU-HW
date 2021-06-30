for i = 1:11
    subplot(3, 4, i);
    ims = -.1 + .1 * i;
    imshow(ims);
    str = 'gray scale =';
    title(strcat(str, num2str(ims)));
end
