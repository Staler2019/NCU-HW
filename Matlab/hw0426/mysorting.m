function out = mysorting(in)
    out = in;

    for ii = 1:size(out,2) - 1

        for jj = ii + 1:size(out,2)

            if out(jj) > out(ii)
                % swap
                tmp = out(jj);
                out(jj) = out(ii);
                out(ii) = tmp;
            end

        end

    end

end
