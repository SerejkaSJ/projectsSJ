
"use strict";

var map         = null;
var markers     = [];
var bounds      = null;
var current_id  = 2;
var locations = [
  // Шаблон: id, название места, id страны, координаты-lat, координаты-lng, название отеля,       url отеля,                                                                                                      цена за ночь
  // [        1, 'Гданьск',      'pl',      54.36667,       18.63333',      'Focus hotel Gdansk', 'https://www.booking.com/hotel/pl/focus-gdansk.ru.html?aid=304142;sid=b685d59d8828198d7827e9c5b595ff9a;dcid=5', '50']
  // Важно !!!!!
  // id=0 - начало маршрута !!!!!
  // id=1 - конец маршрута !!!!!
];
var ordered_list = [];






/****************************
 *
 * Очистка маркеров карты
 *
 ****************************/
function clear_map_markers() {
    while (markers.length) {
        markers.pop().setMap(null);
    }
    markers.length = 0;
    bounds = null;
}








/****************************
 *
 * Обновление и перерисовка маркеров карты
 *
 ****************************/
function renew_map_markers() {
    if (0 === locations.length)
        return;

    clear_map_markers();

    var marker, i;

    bounds = new google.maps.LatLngBounds();

    //
    // Расстановка маркеров начала и конца маршрута
    //
    if (1 === locations.length) {
        marker = new google.maps.Marker({
            position: new google.maps.LatLng(locations[0][3], locations[0][4]),
            icon: 'images/markers/numbers/letter_s.png',
            map: map
        });
        markers.push(marker);
    } else 
        if (locations[0][1] !== locations[1][1]) {
            // Если начальная и конечная точки отличаются
            // Добавляем маркер стартовой точки
            marker = new google.maps.Marker({
                position: new google.maps.LatLng(locations[0][3], locations[0][4]),
                icon: 'images/markers/numbers/letter_s.png',
                map: map
            });
            markers.push(marker);
            // Добавляем маркер конечной точки
            marker = new google.maps.Marker({
                position: new google.maps.LatLng(locations[1][3], locations[1][4]),
                icon: 'images/markers/numbers/letter_f.png',
                map: map
            });
            markers.push(marker);
        } else {
            // Если начальная и конечная точки совпадают
            marker = new google.maps.Marker({
                position: new google.maps.LatLng(locations[0][3], locations[0][4]),
                icon: 'images/markers/numbers/pinother.png',
                map: map
            });
            markers.push(marker);
        }

    //
    // Расстановка маркеров промежуточных точек
    //
    for (i = 0; i < ordered_list.length; i += 1) {
        var n = i + 1;
        marker = new google.maps.Marker({
            position: new google.maps.LatLng(locations[ordered_list[i]][3], locations[ordered_list[i]][4]),
            title: 'Marker #' + n,
            icon: 'images/markers/numbers/number_' + n + '.png',
            map: map
        });
        markers.push(marker);

        /*
        google.maps.event.addListener(marker, 'click', (function(marker, i) {
            return function() {
                infowindow.setContent(locations[i][0]);
                infowindow.open(map, marker);
            }
        })(marker, i));
        //*/
        var infowindow = new google.maps.InfoWindow({
            content: '<div id="content">Hello, marker! :-)</div>'
        });    
        marker.addListener('click', function() {
            infowindow.open(map, marker);
        });
    }

    //
    // Подстраиваем границы карты так, чтобы были видны маркеры
    //
    for (i = 0; i < markers.length; i += 1)
        bounds.extend(markers[i].getPosition());

    if (markers.length == 1)
        map.setCenter(new GLatLng(locations[0][3], locations[0][4]), 10);
    else
        map.fitBounds(bounds);
}






/****************************
 *
 * Получение идентификатора страны по имени
 *
 ****************************/
function GetCountryID(country_name) {
  var country_id = "ru";
  switch(country_name) {
    case "Австрия": 
      country_id = "at";
      break;
    case "Беларусь": 
      country_id = "by";
      break;
    case "Латвия": 
      country_id = "lv";
      break;
    case "Литва":
      country_id = "lt";
      break;
    case "Польша"   : 
    case "Польща"   : 
      country_id = "pl";
      break;
    case "Россия": 
      country_id = "ru";
      break;
    case "Чехия": 
    case "Република Чехия": 
      country_id = "cz";
      break;
  }
  return country_id;
}









/****************************
 *
 * Инициализация карты и элементов ввода контрольных точек маршрута
 *
 ****************************/
function init_map_and_input_controls() {
    var myLocation = new google.maps.LatLng(55.997917, 37.190417);
    var mapOptions = {
        mapTypeId : google.maps.MapTypeId.ROADMAP,
        center    : myLocation,
        zoom      : 10
    };

    map = new google.maps.Map(document.getElementById("map-container"), mapOptions);

    //
    // Инициализация элементов ввода для автодополнения
    //
  
    // Сначала - элемент ввода начальной точки маршрута
    var input_start = /** @type {HTMLInputElement} */(document.getElementById('city-input-start'));
    var autocomplete_start = new google.maps.places.Autocomplete(input_start);
    autocomplete_start.bindTo('bounds', map);
    google.maps.event.addListener(autocomplete_start, 'place_changed', function() {
        var place = autocomplete_start.getPlace();
        if (!place.geometry) {
            window.alert("Для места, возвращённого Google'ом, не задана геометрия!");
            return;
        }
        if (place.geometry.viewport)
            map.fitBounds(place.geometry.viewport);
        else {
            map.setCenter(place.geometry.location);
            map.setZoom(10);
        }

        var country_name    = $('#city-input-start').val().split(",")[$('#city-input-start').val().split(",").length - 1].replace(/ /g,''),
            country_id      = GetCountryID(country_name);

        locations[0] = [0, $('#city-input-start').val(), country_id, place.geometry.location.lat(), place.geometry.location.lng(), 'UNAPPLICABLE', 'UNAPPLICABLE', 0];
        
        if( $('#city-finish-enabled').is(':checked') == false ) {
            $('#city-input-finish').val($('#city-input-start').val());
            locations[1] = [1, $('#city-input-start').val(), country_id, place.geometry.location.lat(), place.geometry.location.lng(), 'UNAPPLICABLE', 'UNAPPLICABLE', 0];
        }
        
        renew_map_markers();
  });
  
  // Затем - элемент ввода конечной точки маршрута
  var input_finish = /** @type {HTMLInputElement} */(document.getElementById('city-input-finish'));
  var autocomplete_finish = new google.maps.places.Autocomplete(input_finish);
  autocomplete_finish.bindTo('bounds', map);
  google.maps.event.addListener(autocomplete_finish, 'place_changed', function() {

      var place = autocomplete_finish.getPlace();
      if (!place.geometry) {
            window.alert("Для места, возвращённого Google'ом, не задана геометрия!");
            return;
      }

      if (place.geometry.viewport)
            map.fitBounds(place.geometry.viewport);
      else {
          map.setCenter(place.geometry.location);
          map.setZoom(10);
      }

      var country_name      = $('#city-input-finish').val().split(",")[$('#city-input-finish').val().split(",").length - 1].replace(/ /g,''),
          country_id        = GetCountryID(country_name);

      locations[1] = [1, $('#city-input-finish').val(), country_id, place.geometry.location.lat(), place.geometry.location.lng(), 'UNAPPLICABLE', 'UNAPPLICABLE', 0];

      renew_map_markers();
  });
  
  
  // И, наконец, элемент ввода промежуточных точек
  var input_intermediate = /** @type {HTMLInputElement} */(document.getElementById('city-input-intermediate'));
  var autocomplete_intermediate = new google.maps.places.Autocomplete(input_intermediate);
  autocomplete_intermediate.bindTo('bounds', map);
  google.maps.event.addListener(autocomplete_intermediate, 'place_changed', function() {

      $('#city-location-lat').text('');
      $('#city-location-lng').text('');
      var place = autocomplete_intermediate.getPlace();

      if (!place.geometry) {
          window.alert("Autocomplete's returned place contains no geometry");
          return;
      }

      if (place.geometry.viewport)
          map.fitBounds(place.geometry.viewport);
      else {
          map.setCenter(place.geometry.location);
          map.setZoom(10);
      }

      $('#city-location-lat').text(place.geometry.location.lat());
      $('#city-location-lng').text(place.geometry.location.lng());
  });
}







/****************************
 *
 * Подгон масштаба карты под все маркеры
 *
 ****************************/
function fit_map_to_markers() {
    //
    // Подстраиваем границы карты так, чтобы были видны маркеры
    //
    bounds = new google.maps.LatLngBounds();
    for (i = 0; i < markers.length; i += 1)
        bounds.extend(markers[i].getPosition());

    if (markers.length == 1)
        map.setCenter(new GLatLng(locations[0][3], locations[0][4]), 10);
    else
        map.fitBounds(bounds);
}


