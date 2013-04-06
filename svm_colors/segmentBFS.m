function [seg_img, class_ctr, class_mass] = segmentBFS(img)
    
    class_idx = 1;

    [m,n] = size(img);

    seg_img = zeros(size(img));

    buf_size = [1,1];

    buf_img = padarray(img, buf_size);

    current_pos = [1,1] + buf_size;
    lower_bound = [1,1] + buf_size;
    upper_bound = size(img) + buf_size;

    class_index = 1;
    
    class_mass = [0];
    class_ctr = [0,0];

    % Iterate row-by-row
    for i=lower_bound(1):upper_bound(1)
        for j=lower_bound(2):upper_bound(2)
            
            if (buf_img(i,j) ~= 0) &&( seg_img(i - buf_size(1),j - buf_size(2)) == 0)
                % Do BFS here
                bfs_queue = [i,j];
                seg_img(i - buf_size(1), j - buf_size(2)) = class_index;

                class_mass(class_index) = [0];
                class_ctr(class_index,:) = [0,0];
                
                while ~isempty(bfs_queue)
                    
                    current_pos = bfs_queue(1,:);
                    seg_pos = current_pos - lower_bound;
                    
                    class_ctr(class_index,:) = class_ctr(class_index,:) ...
                        + bfs_queue(1,:);

                    class_mass(class_index) = ...
                        class_mass(class_index) + 1;
                    
                    bfs_queue(1,:) = [];

                    % Relative to image coordinates, where top left is (0, 0)
                    left  = current_pos - [1, 0];
                    right = current_pos + [1, 0];
                    up    = current_pos - [0, 1];
                    down  = current_pos + [0, 1];

                    if (buf_img(left(1), left(2)) ~= 0 && seg_img(left(1) ...
                                                                  - ...
                                                                  buf_size(1), left(2) - buf_size(2)) == 0)
                        seg_img(left(1) - buf_size(1), left(2) ...
                                        - buf_size(2))= class_index;
                        bfs_queue = [bfs_queue; left];
                    end
                    if (buf_img(right(1), right(2)) ~= 0 && ...
                        seg_img(right(1) - buf_size(1), right(2) - ...
                                buf_size(2)) == 0)
                        seg_img(right(1) - buf_size(1), ...
                                        right(2) - buf_size(2))= class_index;
                        bfs_queue = [bfs_queue; right];
                    end
                    if (buf_img(up(1), up(2)) ~= 0 && seg_img(up(1) ...
                                                              - ...
                                                              buf_size(1), up(2) - buf_size(2)) == 0)
                        seg_img(up(1) - buf_size(1), up(2) ...
                                        - buf_size(2))= class_index;
                        bfs_queue = [bfs_queue; up];
                    end
                    if (buf_img(down(1), down(2)) ~= 0 && seg_img(down(1) ...
                                                                  - ...
                                                                  buf_size(1), down(2) - buf_size(2)) == 0)
                        seg_img(down(1) - buf_size(1), down(2) ...
                                        - buf_size(2))= class_index;
                        bfs_queue = [bfs_queue; down];
                    end

                end
                
                % Search is over, increment the pixel group index
                class_ctr(class_index,:) = ...
                    class_ctr(class_index,:) / class_mass(class_index);
                
                class_index = class_index + 1;
            
            end
            
        end
    end

end