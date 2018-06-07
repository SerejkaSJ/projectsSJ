local apple, snake, direction, width, height, delay

function love.load()
	width = love.graphics.getWidth() / 10			
	height = love.graphics.getHeight() /10			
	
	apple = { x = math.random(width);				
			  y = math.random(height); } 			
	snake = { } 		
	local x_cor = math.random(width);
	local y_cor = math.random(height);
	for i = 1, 5 do 						
		point = { x = x_cor;						
				  y = y_cor + i; }					
		table.insert(snake, point)					
	end
	direction = "up"								--змейка должна куда то ползти
	delay = 0									--змейка не должна быть нервной
end

function love.update(dt)
	--[[for k, v in pairs(snake) do  					--Проверяем не съела-ла змейка саму себя
		if k ~= 1 and snake[1].x == v.x and
					  snake[1].y == v.y then
			print("You died :3")					--смотрим на все с улыбкой (:
			love.event.quit()
		end
	end]]
	if delay % 2 == 0 then							
		if apple.x == snake[1].x and
		   apple.y == snake[1].y then
				apple = { x = math.random(width);		--вот и поели, генерируем X-координату
						  y = math.random(height); } 	--и Y..
		else 											--не сразу ясно, но понятно
			table.remove(snake, table.getn(snake)) 		--убираем последний элемент и добавляем его в начало
		end

		if direction == "up" then					--ну тут вроде все ясно, обрабатываем направление
			table.insert(snake, 1, { x = snake[1].x;
									 y = (snake[1].y - 1) % height; })
		elseif direction == "down" then
			table.insert(snake, 1, { x = snake[1].x;
									 y = (snake[1].y + 1) % height; })
		elseif direction == "left" then
			table.insert(snake, 1, { x = (snake[1].x - 1) % width;
									 y = snake[1].y; })
		elseif direction == "right" then 
			table.insert(snake, 1, { x = (snake[1].x + 1) % width;
									 y = snake[1].y; })
		elseif direction == "stop"  then 
			table.insert(snake,  { x = snake[1].x;
								   y = snake[1].y;})
		end
	end
	delay = delay + 1
end

function love.keypressed(key)						

	if key == "up" then
		direction = "up"
	elseif key == "down" then
		direction = "down"
	elseif key == "left" then
		direction = "left"
	elseif key == "right" then
		direction = "right"
	elseif key == "p" then
		direction = "stop"
	elseif key == "escape" then
		love.event.quit()
	end
end

function love.draw()
	love.graphics.setBackgroundColor(150, 150, 150)		
	love.graphics.setColor(0, 0, 255)				
	for k, v in pairs(snake) do 					--отрисовываем каждую клетку
		love.graphics.rectangle("fill", v.x * 10, v.y * 10, 10, 10)
	end
	love.graphics.setColor(0, 255, 0)		
	love.graphics.rectangle("fill", apple.x * 10, apple.y * 10, 10, 10)
end