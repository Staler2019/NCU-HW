function area = area2d(mat)
    area = (1/2) * (mat(1,1)*(mat(2,2)-mat(2,3)) - mat(1,2)*(mat(2,1)-mat(2,3)) + mat(1,3)*(mat(2,1)-mat(2,2)));
    area = abs(area);
end