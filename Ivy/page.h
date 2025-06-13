#ifndef IVYPAGE_H
#define IVYPAGE_H

#include <Arduino.h>

String page = R"rawliteral(

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ivy UI</title>
    <style>
        *, *::before, *::after {
            box-sizing: border-box;
        }

        body {
          /*  font-family: Geneva, Verdana, sans-serif;*/
            font-family: 'Inter', 'Roboto', 'Segoe UI', 'Helvetica Neue', Arial, sans-serif;
            display: flex;
            justify-content: center;
            color: white;
            background-image: repeating-linear-gradient(
                -45deg,
                rgb(9, 32, 34),
                rgb(9, 32, 34) 10px,
                rgb(9, 31, 34) 10px,
                rgb(9, 31, 34) 20px
            );
        }

        .panel {
            border: solid rgb(26, 148, 138) 1px;
            background: rgba(26, 148, 138, 0.384);
            /*background-color: rgba(26, 148, 138, 0.384);*/
            border-radius: 5px;
            padding: 0.5em;
            width: 100%;
            margin-top: 1rem;
        }
            th {
                text-align: center;
                padding: 0.2rem 1rem;
            }

            table tr:nth-child(even) {
                background-color: #00000011;
            }
            
            td {
                padding: 0.4rem 0.7rem;
                height: 2rem;
                text-align: center;                
            }
        


        .unit-box {
            width: 100%; /* Or variable size */
            height: 100px;
            display: flex;
            justify-content: center;
            align-items: center;
            font-size: clamp(10px, 10vw, 50px);
            font-weight: bold;
            text-align: center;
        }

        .plot {
            background: #1111116e; 
            border: solid #00000034 1px;
            box-shadow: inset 0 0 10px #00000024;
            border-radius: 8px; 
            height: 200px;
            overflow: hidden;
            margin: 0.25rem;
            position: relative;
        }

        .ghosty {
            transition: opacity 0.12s;
            opacity: 0.5;
        }
            .ghosty:hover{
                opacity: 1;
            }

        .unknown {
            pointer-events: none;
            user-select: none;
            opacity: 0.2;
        }

        .button-rack {
            display: flex;
            overflow: hidden;
            border: 1px solid #00000034;
            border-radius: 5px 0 5px 0;
            font-weight: bold;
            background-color: #26413c;
        }
            .button-rack.vertical {
                flex-direction: column-reverse;
            }
            
            .button-rack > .button {
                flex: 1;
                padding: 4px 8px;
                cursor: pointer;
                transition: background-color 0.12s;
                user-select: none;
                border-left: solid #00000034 1px;
                border-right: solid #00000034 1px;
                text-align: center;
                opacity: 0.5;
            }
                .button-rack > .button.on {
                    background-color: #15a185;
                    opacity: 1;
                }

                .button-rack > .button.on.red {
                    background-color: #a83b53;
                }

                .button-rack > .button.on.orange {
                    background-color: #aa772b;
                }

        .light-symbol {
            border-radius: 5px 0 5px 0;
            border: 1px solid #00000034;
            background-color: #26413c;
            opacity: 0.5;
        }
            .light-symbol.on{
                border: 3px solid #16ctemp5a5;
                background-color: #1a9b83;
                opacity: 1;
            }

        .invisible{
          display: none;
        }
    </style>
</head>
<body>
    <!-- Lamp Symbol -->
    <svg style="display: none;">
        <symbol id="lamp-icon-on" viewBox="0 0 512 512">
            <g stroke="none" stroke-width="1" fill="#fff" fill-rule="evenodd" transform="translate(42.666667, 21.333333)">
                <path d="M213.333333,85.3333333 C284.025781,85.3333333 341.333333,142.640885 341.333333,213.333333 C341.333333,260.711239 315.5928,302.077122 277.333732,324.208982 L277.333333,405.333333 L256,426.666667 L234.666667,426.666667 C234.666667,438.448741 225.115408,448 213.333333,448 C201.551259,448 192,438.448741 192,426.666667 L192,426.666667 L170.666667,426.666667 L149.333333,405.333333 L149.332954,324.208993 C111.073876,302.077136 85.3333333,260.711248 85.3333333,213.333333 C85.3333333,142.640885 142.640885,85.3333333 213.333333,85.3333333 Z M234.667665,339.563386 C227.72957,340.727434 220.602209,341.333333 213.333333,341.333333 C206.064458,341.333333 198.937097,340.727434 191.999002,339.563386 L192,384 L234.666667,384 L234.667665,339.563386 Z M96.4250122,307.614237 L119.052429,330.241654 L73.7975952,375.496488 L51.1701782,352.869071 L96.4250122,307.614237 Z M330.241654,307.614237 L375.496488,352.869071 L352.869071,375.496488 L307.614237,330.241654 L330.241654,307.614237 Z M213.333333,128 C166.205035,128 128,166.205035 128,213.333333 C128,260.461632 166.205035,298.666667 213.333333,298.666667 C260.461632,298.666667 298.666667,260.461632 298.666667,213.333333 C298.666667,166.205035 260.461632,128 213.333333,128 Z M426.666667,197.333333 L426.666667,229.333333 L362.666667,229.333333 L362.666667,197.333333 L426.666667,197.333333 Z M64,197.333333 L64,229.333333 L3.55271368e-14,229.333333 L3.55271368e-14,197.333333 L64,197.333333 Z M352.869071,51.1701782 L375.496488,73.7975952 L330.241654,119.052429 L307.614237,96.4250122 L352.869071,51.1701782 Z M73.7975952,51.1701782 L119.052429,96.4250122 L96.4250122,119.052429 L51.1701782,73.7975952 L73.7975952,51.1701782 Z M229.333333,-1.0658141e-14 L229.333333,64 L197.333333,64 L197.333333,-1.0658141e-14 L229.333333,-1.0658141e-14 Z"></path>
            </g>
        </symbol>
        <symbol id="lamp-icon-off" viewBox="0 0 512 512">
            <g stroke="none" stroke-width="1" fill="#fff" fill-rule="evenodd" transform="translate(42.666667, 21.333333)">
                <path d="M213.333333,85.3333333 C284.025781,85.3333333 341.333333,142.640885 341.333333,213.333333 C341.333333,260.711239 315.5928,302.077122 277.333732,324.208982 L277.333333,405.333333 L256,426.666667 L234.666667,426.666667 C234.666667,438.448741 225.115408,448 213.333333,448 C201.551259,448 192,438.448741 192,426.666667 L192,426.666667 L170.666667,426.666667 L149.333333,405.333333 L149.332954,324.208993 C111.073876,302.077136 85.3333333,260.711248 85.3333333,213.333333 C85.3333333,142.640885 142.640885,85.3333333 213.333333,85.3333333 Z M234.667665,339.563386 C227.72957,340.727434 220.602209,341.333333 213.333333,341.333333 C206.064458,341.333333 198.937097,340.727434 191.999002,339.563386 L192,384 L234.666667,384 L234.667665,339.563386 Z M213.333333,128 C166.205035,128 128,166.205035 128,213.333333 C128,260.461632 166.205035,298.666667 213.333333,298.666667 C260.461632,298.666667 298.666667,260.461632 298.666667,213.333333 C298.666667,166.205035 260.461632,128 213.333333,128 Z"></path>
            </g>
        </symbol>
    </svg>

    <!-- Actual Page -->
    
    <div style="margin: auto; display: flex; flex-direction: column; width: 100%; max-width: 800px; justify-content: center;">
        <div style="display: flex; align-items: center">
          <div id="view-clock" style="margin-left: 0.5rem">03:57</div>
          <div id="view-ntp-avail" style="margin-left: 1rem; height: 2rem; border: 1px solid red; background-color: #ff000034; color white; font-weight: bold; padding: 0.2rem 1rem; border-radius: 5px">No se pudo obtener la hora de internet!</div>
        </div>
        <div style="display: flex; justify-content: space-around;" class="panel">
            <div style="width: 50%; display: flex; flex-direction: column;">
                <div class="unit-box"><span id="view-temperature">--</span>°C</div>
                <div class="plot" id="view-plot-temperature">
                  <svg id="tplot" viewBox="0.5 -5 99 110" preserveAspectRatio="none" style="width:100%; height:200px; position: absolute; mix-blend-mode: lighten;"></svg>
                  <div class="button-rack ghosty" data-target="temperature" style="position: absolute; border-left: none;">
                    <div class="button" data-value="0">24h</div>
                    <div class="button" data-value="1">1h</div>
                    <div class="button" data-value="2">5min</div>
                  </div>
                </div>
            </div>
            
            <div style="width: 50%; display: flex; flex-direction: column;">
                <div class="unit-box"><span id="view-humidity">--</span>%RH</div>
                <div class="plot" id="view-plot-humidity">
                  <svg id="hplot" viewBox="0.5 -5 99 110" preserveAspectRatio="none" style="width:100%; height:200px; position: absolute; mix-blend-mode: lighten;"></svg>
                  <div class="button-rack ghosty" data-target="humidity" style="position: absolute; border-left: none;">
                    <div class="button" data-value="0">24h</div>
                    <div class="button" data-value="1">1h</div>
                    <div class="button" data-value="2">5min</div>
                  </div>
                </div>
            </div>
        </div>
        <div class="panel">
            <table style="width: 100%; color: white; border-collapse: collapse;">
                <thead>
                    <tr>
                    </tr>
                </thead>
                <tbody id="outlet-table-body">
                </tbody>
            </table>
        </div>
        <div style="background-color: #00000034; padding: 0.5rem; position: stiky; bottom: 0; right: 0; z-index: -10; font-size: 0.8rem;"> Hecho en Catriel - por Rhodune! Lab - con Amor ♥️</div>
    </div>

    <script>
      /* Generate the buttons */
      window.addEventListener('DOMContentLoaded', () => {
        const tbody = document.getElementById('outlet-table-body');
        for (let i = 0; i < 8; i++) {
            const tr = document.createElement('tr');
            tr.innerHTML = `
                <td style="text-align: left; font-size: 1.3rem; text-overflow: ellipsis">
                    <b id="view-outlet-label-${i}">--</b>
                </td>
                <td>
                    <div data-target="mode" data-index="${i}" id="view-btn-rack-mode-${i}" class="button-rack vertical">
                        <div data-value="1" class="button orange" id="view-btn-manual-${i}">MANUAL</div>
                        <div data-value="0" class="button" id="view-btn-auto-${i}">AUTO</div>
                    </div>
                </td>
                <td>
                    <div data-target="switch" data-index="${i}" id="view-btn-rack-switch-${i}" class="button-rack">
                        <div data-value="0" class="button red on" id="view-btn-off-${i}">
                            <div style="padding: 0; margin: auto; width: 20px; height: 20px; border: solid white 3px; border-radius: 10px;"></div>
                        </div>
                        <div data-value="1" class="button" id="view-btn-on-${i}">
                            <div style="padding: 0; margin: auto; width: 0px; height: 20px; border: solid white 2px; border-radius: 10px;"></div>
                        </div>
                    </div>
                </td>
                <td style="width: 4rem">
                    <svg id="view-outlet-state-${i}" style="height: 2rem; width: 3rem;" class="light-symbol">
                        <use id="view-lamp-${i}" href="#lamp-icon-off" />
                    </svg>
                </td>
            `;
            tbody.appendChild(tr);
        }
        document.querySelectorAll('.button-rack').forEach(rack => {
          rack.addEventListener('click', e => {
              if (!e.target.classList.contains('button')) return;
              const target = rack.dataset.target;
              const index = parseInt(rack.dataset.index, 10);
              const value = parseInt(e.target.dataset.value, 10);

              switch(target)
              {
                case 'humidity':
                  view_humidity_plot_window = value;
                  break;

                case 'temperature':
                  view_temp_plot_window = value;
                  break;

                case 'mode':
                  fetch(`/mode?index=${index}&mode=${value}`)
                    .then(res => res.text())
                    .then(data => console.log(`Ivy Server: ${data}`));
                  break;

                case 'switch':
                  fetch(`/switch?index=${index}&state=${value}`)
                    .then(res => res.text())
                    .then(data => console.log(`Ivy Server: ${data}`));
                  break;
              }

              // Remove "on" from all, add to clicked
              [...rack.children].forEach(btn => btn.classList.remove('on'));
              e.target.classList.add('on');
              setTimeout(() => {
                pollIvy();
              }, 500);
          });
        });

        pollIvy();
        setInterval(pollIvy, 8000);
        
        document.querySelector('[data-target="temperature"] .button[data-value="0"]').click();
        document.querySelector('[data-target="humidity"] .button[data-value="0"]').click();
      });
      
      
      function drawSVGPlot(svg, data, color = "turquoise") {
        try {
            // Ensure data is actually an array of finite numbers
            if (!Array.isArray(data) || data.length === 0) throw new Error("Bad data");
            const cleanedData = data.map(Number).filter(v => Number.isFinite(v));
            if (cleanedData.length < 2) throw new Error("Not enough valid data");

            const w = 100, h = 100;
            const min = Math.min(...cleanedData);
            const max = Math.max(...cleanedData);
            const range = max - min || 1;

            const points = cleanedData.map((v, i) => {
                const x = (i / (cleanedData.length - 1)) * w;
                const y = h - ((v - min) / range) * h;
                return `${x},${y}`;
            });

            const fillPath = `M0,${h} L${points.join(" ")} L${w},${h} Z`;
            const strokePath = `M${points.join(" L")}`;

            svg.innerHTML = `
                <defs>
                    <linearGradient id="plotGradient" gradientTransform="rotate(90)">
                        <stop offset="40%" stop-color="${color}" stop-opacity="0.3" />
                        <stop offset="100%" stop-color="${color}" stop-opacity="0" />
                    </linearGradient>
                </defs>
                <path d="${fillPath}" fill="url(#plotGradient)" stroke="none"/>
                <path d="${strokePath}" fill="none" stroke="${color}" stroke-width="0.8" />
            `;
        } catch (err) {
            console.warn("drawSVGPlot fallback due to:", err);
            svg.innerHTML = `
                <text x="50%" y="50%" text-anchor="middle" dominant-baseline="middle" font-size="10" fill="#ffffff34">
                    --
                </text>
            `;
        }
      }



      /* We preload links here */
      
      const view_temp_plot = document.getElementById("tplot");
      const view_humidity_plot = document.getElementById("hplot");
      const view_clock = document.getElementById("view-clock");
      const view_ntp_avail = document.getElementById("view-ntp-avail");

      // 0 = 24h, 1 = 1h, 2 = 5m
      let view_temp_plot_window = 0;
      let view_humidity_plot_window = 0;

      async function pollIvy(){
        const res = await fetch('/status');
        const status_json = await res.json();

        view_clock.textContent = status_json.clock;

        view_ntp_avail.classList.toggle("invisible", status_json.ntp === 1);

        if     (view_temp_plot_window === 0) drawSVGPlot(view_temp_plot, status_json.temp.log.last_24_hours);
        else if(view_temp_plot_window === 1) drawSVGPlot(view_temp_plot, status_json.temp.log.last_hour);
        else if(view_temp_plot_window === 2) drawSVGPlot(view_temp_plot, status_json.temp.log.last_5_minutes);

        if     (view_humidity_plot_window === 0) drawSVGPlot(view_humidity_plot, status_json.humidity.log.last_24_hours);
        else if(view_humidity_plot_window === 1) drawSVGPlot(view_humidity_plot, status_json.humidity.log.last_hour);
        else if(view_humidity_plot_window === 2) drawSVGPlot(view_humidity_plot, status_json.humidity.log.last_5_minutes);

        document.getElementById("view-temperature").textContent = status_json.temp.current === 65535 ? "--" : status_json.temp.current;
        document.getElementById("view-humidity").textContent = status_json.humidity.current === 65535 ? "--" : status_json.humidity.current;

        status_json.outlets.forEach((outlet, index) => {
          const label = document.getElementById(`view-outlet-label-${index}`);
          if (label && outlet.label) {
            label.textContent = outlet.label;
          }

          const btn_manual = document.getElementById(`view-btn-manual-${index}`);
          const btn_auto = document.getElementById(`view-btn-auto-${index}`);
          const btn_rack = document.getElementById(`view-btn-rack-mode-${index}`);
          const view_lamp = document.getElementById(`view-outlet-state-${index}`);
          const view_lamp_icon = document.getElementById(`view-lamp-${index}`);
          
          btn_auto.classList.toggle("on", outlet.mode === 0);
          btn_manual.classList.toggle("on", outlet.mode === 1);
          btn_rack.classList.toggle("unknown", outlet.mode > 1 || outlet.mode < 0 || (outlet.mode === undefined));

          document.getElementById(`view-btn-on-${index}`).classList.toggle("on", outlet.state === 1);
          document.getElementById(`view-btn-off-${index}`).classList.toggle("on", outlet.state === 0);

          view_lamp.classList.toggle("on", outlet.state === 1);
          if (outlet.state === 1) {
            view_lamp_icon.setAttribute('href', '#lamp-icon-on');
          } else {
            view_lamp_icon.setAttribute('href', '#lamp-icon-off');
          }
        });
      }
    </script>
</body>
</html>

)rawliteral";

#endif