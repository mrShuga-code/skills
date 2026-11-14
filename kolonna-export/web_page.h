// web_page.h — страницы веб-интерфейса (HTML + CSS + JS в одном файле).
// Цвета и раскладка — как в макете контроллера. Светлая и тёмная тема по
// настройке телефона/компьютера.
#pragma once
#include <Arduino.h>

// =====================================================================
//  Монитор: http://kolonna.local/
// =====================================================================
static const char PAGE_MAIN[] PROGMEM = R"HTML(<!doctype html>
<html lang="ru"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Колонна</title>
<style>
:root{--bg:#f3f4f1;--surface:#fff;--fg:#1b1f1d;--muted:#5d6762;--line:#d9ddd8;--accent:#2f6b55;
--ok:#1e8a4c;--warn:#a77a00;--hot:#c9600c;--bad:#c83232;--cold:#1a7fbf;--stab:#3654c9;
--ok-t:#e3f3ea;--warn-t:#fbf1d3;--hot-t:#fbe6d5;--bad-t:#fbe1e1;--cold-t:#e0f0fa;--stab-t:#e4e9fb;--cur:#e02020}
@media(prefers-color-scheme:dark){:root{--bg:#121614;--surface:#1a1f1c;--fg:#e8ece9;--muted:#9aa49f;--line:#2c332f;--accent:#6fbf9c;
--ok:#4fd18a;--warn:#f2c94c;--hot:#ff9a4a;--bad:#ff6b6b;--cold:#5ec2ff;--stab:#8ea2ff;
--ok-t:#173226;--warn-t:#3a3216;--hot-t:#3d2716;--bad-t:#3e1d1d;--cold-t:#15303f;--stab-t:#1f2647;--cur:#ff3b3b;color-scheme:dark}}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--fg);font:15px/1.5 system-ui,-apple-system,"Segoe UI",Roboto,sans-serif}
.wrap{max-width:980px;margin:0 auto;padding:16px;display:grid;gap:14px}
header{display:flex;flex-wrap:wrap;justify-content:space-between;align-items:center;gap:8px 16px}
h1{font-size:19px;margin:0}
.meta{font-size:13px;color:var(--muted);display:flex;flex-wrap:wrap;gap:6px 14px;align-items:center}
.meta b{color:var(--fg);font-variant-numeric:tabular-nums}
a{color:var(--accent)}
button{font:600 14px system-ui,sans-serif;border:1px solid var(--line);border-radius:8px;padding:9px 14px;background:var(--surface);color:var(--fg);cursor:pointer}
.btn{background:var(--bad);color:#fff;border:0}.btn.cold{background:var(--cold)}
.banner{display:flex;flex-wrap:wrap;align-items:center;justify-content:space-between;gap:12px;padding:12px 14px;border-radius:10px;font-weight:600}
.banner.bad{background:var(--bad-t);color:var(--bad)}.banner.cold{background:var(--cold-t);color:var(--cold)}.banner.good{background:var(--ok-t);color:var(--ok)}
.banner.hot{background:var(--hot-t);color:var(--hot)}.btn.hot{background:var(--hot)}
.cards{display:grid;grid-template-columns:repeat(auto-fit,minmax(210px,1fr));gap:12px}
.card{background:var(--surface);border:1px solid var(--line);border-left:6px solid var(--line);border-radius:10px;padding:10px 14px;display:grid;gap:2px;min-width:0}
.card .k{font-size:13px;color:var(--muted)}
.card .v{font:700 36px/1.1 ui-monospace,"SFMono-Regular",Consolas,monospace;font-variant-numeric:tabular-nums}
.card .s{font-size:13px;color:var(--muted)}
.chart{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:10px 12px}
.chart h3{margin:0 0 4px;font-size:14px;font-weight:600}.chart h3 span{color:var(--muted);font-weight:400}
canvas{width:100%;height:230px;display:block;touch-action:pan-y;cursor:crosshair}
/* полоска-курсор (14.11.2026): справа вверху графика время и температура в точке, «×» убирает */
.chart .hd{display:flex;justify-content:space-between;align-items:center;gap:8px;min-height:24px;margin:0 0 4px}.chart .hd h3{margin:0}
.chart .cur{display:flex;align-items:center;gap:6px;color:var(--cur);font:600 14px ui-monospace,Consolas,monospace;font-variant-numeric:tabular-nums;white-space:nowrap}
.chart .cur button{padding:0 9px;line-height:22px;color:var(--cur);border-color:var(--cur);font-weight:700}
.tools{display:flex;flex-wrap:wrap;gap:8px 14px;align-items:center}
.seg{display:flex;gap:6px;flex-wrap:wrap}
.seg button{padding:6px 12px;font-weight:500}
.seg button[aria-pressed=true]{background:var(--accent);color:#fff;border-color:var(--accent)}
.sel{display:grid;grid-template-columns:repeat(auto-fit,minmax(240px,1fr));gap:12px}
.sel button{padding:22px 18px;text-align:left;display:grid;gap:6px}
.sel button span{font-size:19px}.sel button em{font-style:normal;font-weight:400;color:var(--muted);font-size:14px}
.sel button.cur{border:2px solid var(--ok)}.sel button .c{color:var(--ok);font-weight:600}
.charts{display:grid;gap:12px}
.fx{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:12px 14px;display:grid;gap:8px}
.fx .top{display:flex;flex-wrap:wrap;align-items:center;gap:8px 12px}.fx h2{font-size:15px;margin:0}
.pill{font-size:12px;font-weight:600;padding:2px 9px;border-radius:999px;background:var(--line);color:var(--fg)}
.pill.active{background:var(--ok-t);color:var(--ok)}.pill.nodata{background:var(--surface);color:var(--muted);border:1px solid var(--line)}
.pill.confirm{background:var(--warn-t);color:var(--warn)}
.fx .vals{display:flex;flex-wrap:wrap;gap:4px 18px;font-size:14px}.fx .vals b{font:700 17px ui-monospace,Consolas,monospace;font-variant-numeric:tabular-nums}
.fx .s{font-size:13px;color:var(--muted)}.fx .row{display:flex;flex-wrap:wrap;gap:8px}
.fx button.go{background:var(--ok);color:#fff;border:0}.fx button:disabled{opacity:.45;cursor:default}
.msg{font-size:13px;font-weight:600}.msg.bad{color:var(--bad)}.msg.good{color:var(--ok)}
.ev{width:100%;border-collapse:collapse;font-size:13px}.ev td,.ev th{padding:4px 6px;border-top:1px solid var(--line);text-align:left;vertical-align:top}
.ev th{color:var(--muted);font-weight:500}.ev td.n{font-variant-numeric:tabular-nums;white-space:nowrap}
.evw{max-height:260px;overflow:auto}
.logs{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:12px 14px;display:grid;gap:4px}
.logs h2{font-size:15px;margin:0 0 4px}.logs .s{font-size:13px;color:var(--muted);margin:0}
.lg{display:flex;align-items:center;gap:6px 12px;padding:6px 0;border-top:1px solid var(--line);font-size:14px;font-variant-numeric:tabular-nums}
.lg:first-child{border-top:0}.lg>span{flex:1;min-width:0}.lg .live{color:var(--ok);font-weight:600}
.lg a{flex:none;display:inline-flex;align-items:center;min-height:40px;padding:0 14px;border:1px solid var(--line);border-radius:8px;text-decoration:none;font-weight:600}
.rl{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:12px 14px;display:flex;flex-wrap:wrap;align-items:center;gap:8px 14px}
.rl h2{font-size:15px;margin:0}.rl .s{font-size:13px;color:var(--muted);flex-basis:100%}
.pill.on{background:var(--ok-t);color:var(--ok)}
.rl button.go{background:var(--ok);color:#fff;border:0}.rl button:disabled{opacity:.45;cursor:default}
[hidden]{display:none!important}
.uom{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:12px 14px;display:flex;flex-wrap:wrap;align-items:center;gap:8px 14px}
.uom h2{font-size:15px;margin:0}.uob{display:grid;grid-template-columns:repeat(5,1fr);gap:8px;flex-basis:100%}
@media(max-width:600px){.uob{grid-template-columns:1fr 1fr}.uob button.e{grid-column:1/-1}}
.uob button{padding:12px 6px;font-size:15px;border-radius:8px;border:1px solid var(--line);background:var(--bg);color:var(--fg)}
.uob button.on.h{background:var(--warn-t);border-color:var(--warn);color:var(--warn);font-weight:700}
.uob button.on.b{background:var(--ok-t);border-color:var(--ok);color:var(--ok);font-weight:700}
.uob button.on.t{background:var(--hot-t);border-color:var(--hot);color:var(--hot);font-weight:700}
.uob button.on.c{background:var(--bad-t);border-color:var(--bad);color:var(--bad);font-weight:700}
.uob button.e{border-color:var(--stab);color:var(--stab)}.uos{font-size:13px;color:var(--muted);flex-basis:100%}
</style></head><body><div class="wrap">
<header><h1 id="title">Колонна</h1>
<div class="meta"><span id="net">…</span><span id="clock"></span>
<span id="runt" hidden><span id="runtL">ПЕРЕГОНКА</span> <b id="el">0:00:00</b> <span id="since"></span></span>
<button id="change" hidden>Сменить перегон</button><a href="/settings">Настройки</a></div></header>

<div id="sel" hidden>
<div class="banner bad" id="bReboot" hidden><span id="bRebootT"></span><button class="btn" data-c="rebootok">Понятно</button></div>
<div class="banner cold" id="bBoot" hidden><span id="bBootT"></span><button class="btn" id="bootNew">Новый перегон</button><button class="btn cold" id="bootGo">Продолжить</button></div>
<p>Выберите перегон. Экран контроллера переключится вместе со страницей.</p>
<div class="sel">
<button id="s1"><span>Первый перегон</span><em>Куб и царга по цветам, датчик 3 показывает воздух.</em><em class="c" id="s1c" hidden></em></button>
<button id="s2"><span>Второй перегон</span><em>Тфикс царги, тревога на хвосты, куб и узел отбора.</em><em class="c" id="s2c" hidden></em></button>
<button id="s3"><span>Экстракция</span><em>Экстрактор Сокслета: только температура куба и время работы.</em><em class="c" id="s3c" hidden></em></button>
</div></div>

<div id="main" hidden style="display:grid;gap:14px">
<div class="banner bad" id="bAlarm" hidden><span id="bAlarmT"></span><button class="btn" data-c="reset">Сброс тревоги</button></div>
<div class="banner bad" id="bFault" hidden><span id="bFaultT"></span><button class="btn" data-c="reset">Сброс тревоги</button></div>
<div class="banner cold" id="bCool" hidden><span id="bCoolT"></span><button class="btn cold" data-c="cool">Охлаждение включено</button></div>
<div class="banner hot" id="bSteam" hidden><span>Пар в узле отбора. Приступите к стабилизации колонны.</span><button class="btn hot" data-c="steamok">Понятно</button></div>
<div class="banner cold" id="bEnd" hidden><span id="bEndT"></span><button class="btn cold" id="endB">Завершить и сохранить лог</button></div>
<div class="banner hot" id="bSlow" hidden><span id="bSlowT"></span><button class="btn hot" data-c="slowok">Понятно</button></div>
<div class="banner good" id="bNew" hidden></div>
<div class="cards" id="cards"></div>
<div class="fx" id="fx" hidden>
<div class="top"><h2>Тфикс</h2><span class="pill" id="fxSt"></span><span class="s" id="fxWhen"></span></div>
<div class="vals"><span>Царга <b id="fxCur">——</b></span><span>Тфикс <b id="fxV">——</b></span><span>ΔT <b id="fxD">——</b></span></div>
<div class="row"><button class="go" id="fxFix">Зафиксировать Тфикс</button><button class="go" id="fxOk" hidden>Подтвердить</button></div>
<div class="msg" id="fxMsg"></div>
<div class="s">Сбросить Тфикс можно только на экране: меню → «Царга».</div>
<div class="evw"><table class="ev"><thead><tr><th>Время</th><th>Событие</th><th>Было → стало</th><th>Царга</th><th>Источник</th></tr></thead><tbody id="ev"></tbody></table></div>
</div>
<div class="tools"><div class="seg" id="per">
<button data-m="30" aria-pressed="true">30 мин</button><button data-m="120" aria-pressed="false">2 часа</button><button data-m="0" aria-pressed="false">вся перегонка</button>
</div><a href="/api/csv" id="csv">Скачать CSV (по минутам)</a></div>
<div class="charts" id="charts"></div>
<section class="uom" id="uom"><h2>Режим отбора</h2><span class="pill" id="uomSt">…</span>
<div class="uob"><button data-u="1" class="h">Отбор голов</button><button data-u="2" class="b">Отбор тела</button><button data-u="3" class="t">Отбор хвостов</button><button data-u="o" class="c" id="uoC">Закрыть отбор</button><button data-u="e" class="e">Конец перегона</button></div>
<div class="uos" id="uoS"></div></section>
<section class="uom" id="end1" hidden><h2>Первый перегон</h2><div class="uob"><button class="e" id="end1B">Конец перегона</button></div><div class="uos">Лог сохранится, экран вернётся к выбору перегона.</div></section>
</div>
<section class="rl" id="relay"><h2>Реле клапана</h2><span class="pill" id="rlSt">…</span>
<button id="rlBtn" disabled>…</button>
<span class="s">Включает и выключает реле электроклапана отбора вручную. После включения питания контроллера реле всегда выключено.</span></section>
<section class="logs" id="logs"><h2>Прошлые перегоны</h2><div id="logl"><p class="s">…</p></div><p class="s" id="logn"></p></section>
</div>
<script>
const $=id=>document.getElementById(id);
const n=(v,d)=>v==null?'——':v.toFixed(d).replace('.',',');
const sgn=(v,d)=>(v>-0.5*Math.pow(10,-d)?'+':'−')+n(Math.abs(v),d);
const hms=s=>Math.floor(s/3600)+':'+String(Math.floor(s/60)%60).padStart(2,'0')+':'+String(s%60).padStart(2,'0');
const mmss=s=>Math.floor(s/60)+':'+String(s%60).padStart(2,'0');
const W={ok:'var(--ok)',warn:'var(--warn)',hot:'var(--hot)',bad:'var(--bad)',cold:'var(--cold)',stab:'var(--stab)',white:'var(--line)',grey:'var(--muted)'};
const T={ok:'var(--ok-t)',warn:'var(--warn-t)',hot:'var(--hot-t)',bad:'var(--bad-t)',cold:'var(--cold-t)',stab:'var(--stab-t)',white:'var(--surface)',grey:'var(--surface)'};
const css=k=>getComputedStyle(document.documentElement).getPropertyValue('--'+k).trim();
let S=null,H=null,per=30,lastRun=-1,evSig='',L=null,logRun=-1;

async function cmd(c,extra){try{await fetch('/api/cmd?c='+c+(extra||''),{method:'POST'});}catch(e){}tick();}
document.querySelectorAll('[data-c]').forEach(b=>b.onclick=()=>cmd(b.dataset.c));
const RN=['','первый перегон','второй перегон','экстракцию'],RN2=['','Первый перегон','Второй перегон','Экстракция'];
const pick=r=>{const o=S&&(S.saved||S.last);   // другой перегон, чем тот, что можно продолжить: сначала «Закончить?»
  if(o&&o!==r&&!confirm('Закончить '+RN[o]+'? Таймер '+hms(S.savedEl||0)+' не продолжится, '+RN2[r]+' начнётся с нуля.'))return;
  cmd('run'+r);};
[1,2,3].forEach(r=>$('s'+r).onclick=()=>pick(r));
$('bootGo').onclick=()=>{if(S&&S.saved)cmd('run'+S.saved);};
$('bootNew').onclick=()=>{if(S&&S.saved&&confirm('Начать новый перегон? '+RN2[S.saved]+' из памяти не продолжится, дальше выберите перегон.'))cmd('fresh');};
const endRun=()=>{if(confirm(S&&S.run===1?'Закончить первый перегон? Лог сохранится, экран вернётся к выбору перегона.':'Закончить второй перегон? Отбор закроется, лог сохранится, экран вернётся к выбору перегона.'))cmd('end');};
$('endB').onclick=endRun;$('end1B').onclick=endRun;   // 14.11.2026: и в первом перегоне
document.querySelectorAll('.uob button').forEach(b=>b.onclick=()=>{if(!S)return;const u=b.dataset.u;
  if(u==='e')endRun();else if(u==='o')cmd(S.uoOpen?'uoclose':'uoopen');else cmd('uo','&m='+u);});
$('rlBtn').onclick=()=>{if(!S)return;$('rlBtn').disabled=true;cmd(S.relay?'relayoff':'relayon');};
$('change').onclick=()=>{if(confirm('Вернуться к выбору перегона? Перегон и таймер сохранятся.'))cmd('select');};
document.querySelectorAll('#per button').forEach(b=>b.onclick=()=>{per=+b.dataset.m;
  document.querySelectorAll('#per button').forEach(x=>x.setAttribute('aria-pressed',x===b));loadHist();});
cmd('time','&t='+Math.floor(Date.now()/1000));   // время для контроллера, если нет интернета

async function tick(){
  try{S=await(await fetch('/api/state',{cache:'no-store'})).json();paint();}
  catch(e){$('net').textContent='нет связи с контроллером';}
}
async function loadHist(){
  if(!S||!S.run)return;
  try{H=await(await fetch('/api/history?m='+per,{cache:'no-store'})).json();hOff=Date.now()/1000-H.now;draw();}catch(e){}
}
// Тфикс: те же слова, что на экране; значение берёт контроллер, страница показывает его ответ
async function fixCmd(c){
  const m=$('fxMsg');
  try{
    const r=await(await fetch('/api/cmd?c='+c,{method:'POST'})).json();
    if(r.ok){m.className='msg good';m.textContent=(c==='fixok'?'Тфикс подтверждена: ':'Тфикс зафиксирована: ')+n(r.fix,2);}
    else{m.className='msg bad';m.textContent='Нельзя: '+r.msg;}
  }catch(e){m.className='msg bad';m.textContent='Нет связи с контроллером';}
  clearTimeout(fixCmd.t);fixCmd.t=setTimeout(()=>{m.textContent='';},6000);
  tick();loadEvents();loadHist();
}
$('fxFix').onclick=()=>{
  const c=S.p[1],cur=c.t!=null?n(Math.round(c.t*100)/100,2):'——';
  let q='Сейчас на царге '+cur+' °C. Новая Тфикс '+cur+'.';
  if(S.fix!=null)q+=' '+(S.wasNow||'Была '+n(S.fix,2))+', заменится.';
  q+=S.mode==='stab'?' Стабилизация прервётся, отбор и пороги пойдут от новой Тфикс.':' «Хвосты» будут считаться от новой Тфикс.';
  q+='\nКонтроллер возьмёт своё измерение в момент команды.';
  if(confirm(q+'\n\nЗафиксировать?'))fixCmd('fix');};
$('fxOk').onclick=()=>{const c=S.p[1];
  if(confirm('Тфикс из памяти: '+n(S.fix,2)+(S.fixAt?' (зафиксирована '+S.fixAt+')':'')+'. Сейчас '+n(c.t,2)+'.\nПодтвердить?'))fixCmd('fixok');};
async function loadEvents(){
  if(!S||S.run!==2)return;
  try{const ev=await(await fetch('/api/events',{cache:'no-store'})).json();
    const sig=JSON.stringify(ev);if(sig===evSig)return;evSig=sig;
    $('ev').innerHTML=ev.length?ev.map(e=>'<tr><td class="n">'+e.time+'</td><td>'+e.what+(e.err?': '+e.err:'')+'</td><td class="n">'+
      (e.old==null?'—':n(e.old,2))+' → '+(e.new==null?'—':n(e.new,2))+'</td><td class="n">'+(e.cur==null?'——':n(e.cur,2))+'</td><td>'+e.from+'</td></tr>').join('')
      :'<tr><td colspan="5">Событий пока нет</td></tr>';
  }catch(e){}
}
// Прошлые перегоны: «№18 · 14.10 12:37 · 36 мин · 1 КБ · Скачать», новые сверху (пароль не нужен)
const dur=m=>m>=60?Math.floor(m/60)+' ч '+(m%60)+' мин':m+' мин';
const kb=b=>Math.max(1,Math.round(b/1024))+' КБ';
// название лога: «Первый перегон №7 от 14.10.2026 12:37» / «Второй перегон №8 от …» (просьба Artem 13.11.2026)
const lname=x=>(x.run===1?'Первый':'Второй')+' перегон №'+x.n+' от '+(x.start?x.start.slice(0,10)+' '+x.start.slice(11,16):'(дата неизвестна)');
async function loadLogs(){
  try{L=await(await fetch('/api/logs',{cache:'no-store'})).json();}catch(e){return;}
  $('logl').innerHTML=!L.fs?'<p class="s">Память для логов не работает</p>':L.logs.length?L.logs.map(x=>'<div class="lg"><span><b>'+lname(x)+'</b> · '+(x.live?'<span class="live">идёт</span>, ':'')+dur(x.min)+' · '+kb(x.size)+
    '</span><a href="/api/csv?n='+x.n+'" download>Скачать</a></div>').join(''):'<p class="s">Перегонов на контроллере пока нет</p>';
  paintLogNote();
}
function paintLogNote(){
  if(!L)return;
  $('logn').textContent=(S&&S.run===1&&!L.run1?'Первый перегон в лог не пишется. ':'')+'Хранятся последние '+L.keep+' перегонов, старые удаляются сами. Удалить — в Настройках.'
    +(L.total?' Свободно во flash '+Math.round(L.free/1024)+' КБ из '+Math.round(L.total/1024)+' КБ'
      +(L.free<L.minFree?': меньше '+Math.round(L.minFree/1024)+' КБ, при старте перегона самый старый лог удалится.':'.'):'');
}
setInterval(tick,1000);tick();
setInterval(loadEvents,3000);
setInterval(loadHist,10000);
setInterval(loadLogs,60000);
addEventListener('resize',()=>draw());

function card(id,key,val,tone,sub){
  return '<div class="card" style="border-left-color:'+W[tone]+';background:'+T[tone]+'"><span class="k">'+key+
  '</span><span class="v" style="color:'+(tone==='white'?'var(--fg)':W[tone])+'">'+val+'</span><span class="s">'+sub+'</span></div>';
}
function paint(){
  const on=S.run>0;
  $('sel').hidden=on;$('main').hidden=!on;$('change').hidden=!on;$('runt').hidden=!on;
  $('bReboot').hidden=!S.reboot;
  if(S.reboot)$('bRebootT').textContent='Контроллер перезапускался: '+S.reboot+'. Отбор закрыт. Выберите перегон («Продолжить» допишет тот же лог).';
  $('bBoot').hidden=!S.boot;
  if(S.boot)$('bBootT').textContent='До выключения шёл '+RN[S.saved].replace('экстракцию','экстракция')+', таймер '+hms(S.savedEl||0)+'. Продолжить его или начать новый?';
  $('net').textContent=S.net==='online'?'● в сети · '+S.ip:S.net==='ap'?'● точка доступа Kolonna-setup':'● подключение к Wi-Fi';
  $('net').style.color=S.net==='online'?'var(--ok)':S.net==='ap'?'var(--warn)':'var(--muted)';
  $('clock').textContent=S.timeOk?S.clock:'';
  $('uom').hidden=S.run!==2;
  $('end1').hidden=S.run!==1;
  if(S.run===2){const u=S.uo||0;
    document.querySelectorAll('.uob button').forEach(b=>{const d=b.dataset.u;b.classList.toggle('on',d==='o'?!S.uoOpen:+d===u);});
    $('uoC').textContent=S.uoOpen?'Закрыть отбор':'Открыть отбор';
    $('uomSt').textContent=['режим не выбран','головы','тело','хвосты'][u]+' · '+(S.valve?'клапан открыт':'клапан закрыт');
    $('uomSt').className='pill'+(S.valve?' on':'');
    let t='';
    if(u===2)t='Пауза клапана: царга выше Тфикс на '+n(S.vDelta,2)+' дольше '+S.vDelay+' с или на '+n(S.vDelta+0.01,2)+' сразу; открывается, когда царга ниже Тфикс (не раньше '+S.vWait+' с). '+
      'Пауз за '+S.pMin+' мин: '+S.pN+' (сигнал при '+S.pLim+') · за перегон: '+S.pCount+
      (S.pause?' · сейчас пауза '+mmss(S.pFor):S.pLast?' · последняя пауза '+mmss(S.pLast):'');
    else if(u===3)t='Клапан открыт всегда. Когда куб дойдёт до '+n(S.tailsEnd,1)+' °C, появится «перегон окончен».';
    else if(u===1)t='Клапан просто открыт, скорость — игольчатым краном.';
    else t='Выберите режим: выбор сразу открывает отбор.';
    $('uoS').textContent=t;}
  $('rlSt').textContent=S.relay?'включено':'выключено';$('rlSt').className='pill'+(S.relay?' on':'');
  $('rlBtn').textContent=S.relay?'Выключить':'Включить';$('rlBtn').className=S.relay?'':'go';$('rlBtn').disabled=false;
  $('title').textContent=on?'Колонна · '+(S.run===3?'экстракция':(S.run===1?'первый':'второй')+' перегон'):'Колонна';
  $('runtL').textContent=S.run===3?'ВРЕМЯ РАБОТЫ':'ПЕРЕГОНКА';
  $('per').parentNode.hidden=S.run===3;$('charts').hidden=S.run===3;   // экстракция: без графиков и CSV
  if(S.run!==logRun){logRun=S.run;loadLogs();}     // список заново при выборе и смене перегона
  $('csv').hidden=S.run===1&&L&&!L.run1;
  if(!on){
    [1,2,3].forEach(r=>{const cur=S.saved===r||S.last===r;$('s'+r).classList.toggle('cur',cur);
      $('s'+r+'c').hidden=!cur;$('s'+r+'c').textContent='продолжить, таймер '+hms(S.savedEl||0);});
    lastRun=0;return;
  }
  $('el').textContent=hms(S.elapsed);$('since').textContent=S.start?'· с '+S.start:'';
  const c=S.p[1],k=S.p[0],u=S.p[2];
  let html='';
  if(S.run===3){
    // экстракция: только куб, без зон и тревог
    html+=card('k','Куб · датчик 1',k.ok&&!S.stale?n(k.t,1):'——',k.ok&&!S.stale?'white':'grey',!k.ok?k.txt:S.stale?'нет свежих данных':'&nbsp;');
    $('bAlarm').hidden=true;$('bFault').hidden=true;$('bNew').hidden=true;
  }else if(S.run===1){
    const ct=S.tone.c;
    html+=card('k','Куб · датчик 1',n(k.t,1),k.ok?S.tone.k:'grey',k.ok?S.zone:k.txt);
    html+=card('c','Царга · датчик 2',n(c.t,1),c.ok?ct:'grey',c.ok?(c.t<S.col1?'ниже ':'от ')+n(S.col1,0):c.txt);
    html+=card('u','Воздух · датчик 3',n(u.t,1),u.ok?'white':'grey',u.ok?'не участвует':u.txt);
    $('bAlarm').hidden=true;$('bFault').hidden=true;$('bNew').hidden=true;
  }else{
    let sub;const d=S.fix!=null&&c.t!=null?c.t-S.fix:0;
    if(!S.valid)sub=(c.ok&&S.stale?'нет свежих данных':c.txt)+(S.fix!=null?' · Тфикс '+n(S.fix,2)+' сохранена':'');
    else if(S.fixState==='confirm')sub='Требуется подтверждение · Тфикс '+n(S.fix,2)+' из памяти · Δ '+sgn(d,2);
    else if(S.mode==='stab'&&S.ask)sub='Стабильно '+(S.win/60)+' мин · зафиксируйте новую Тфикс';
    else if(S.mode==='stab')sub='стабилизация '+mmss(Math.min(S.win,S.stable))+' из '+mmss(S.win)+' · размах '+n(S.spread,2);
    else if(S.fix==null)sub='размах за '+(S.win/60)+' мин '+n(S.spread,2)+(S.spreadReady&&S.spread<=0.0501?' · стабильно, фиксируйте':' · Тфикс не задана');
    else sub='Тфикс '+n(S.fix,2)+' · Δ '+sgn(d,2)+(S.mode==='tails'?' · хвосты':' · отбор');
    html+=card('c','Царга',S.valid?n(c.t,2):'——',S.valid?S.tone.c:'grey',sub);
    html+=card('k','Куб',n(k.t,1),k.ok?S.tone.k:'grey',k.ok?S.zone:k.txt);
    // режим отбора, как на плитке экрана: серая «ЗАКРЫТ», жёлтая «ГОЛОВЫ», зелёная «ТЕЛО»,
    // оранжевая «ХВОСТЫ», серая «ПАУЗА 0:12», красная «ЗАКРЫТ 3:12» (тревога);
    // при неисправном датчике число серое, но подпись остаётся рядом с причиной
    const uoMark='<b>'+S.uoText+'</b>'+(S.valve?' · клапан открыт':' · клапан закрыт');
    html+=card('u','Узел отбора',n(u.t,1),S.uoTone,!u.ok?u.txt+' · '+uoMark:uoMark);
    $('bAlarm').hidden=!S.tails;
    if(S.tails)$('bAlarmT').textContent=S.valid?'Хвосты: царга выше Тфикс на '+n(d,2)+' °C. Закройте отбор.'
      :'Хвосты (тревога держится): нет достоверных данных с царги. Закройте отбор.';
    $('bFault').hidden=!S.faults;
    if(S.faults){const names=['куб','царга','узел отбора'];$('bFaultT').textContent='Неисправен датчик: '+names.filter((x,i)=>S.faults>>i&1).join(', ')+'.';}
    $('bNew').hidden=!(S.newFix||S.ask);
    $('bNew').textContent=S.ask?'Царга стабильна '+(S.win/60)+' мин. Зафиксируйте новую Тфикс (кнопка ниже или на экране).'+(S.wasNow?' '+S.wasNow[0].toUpperCase()+S.wasNow.slice(1)+'.':'')
      :'Новая Тфикс '+n(S.fix,2)+'. Можно открывать отбор.';
    paintFix(c,d);
  }
  $('fx').hidden=S.run!==2;
  $('cards').innerHTML=html;
  $('bCool').hidden=S.cool!==1;
  $('bCoolT').textContent='Куб '+n(k.t,1)+' °C. Включите охлаждение.';
  $('bSteam').hidden=!S.steam;
  $('bSlow').hidden=!S.slow;
  if(S.slow)$('bSlowT').textContent='Частые паузы клапана: '+S.pLim+' за '+S.pMin+' мин. Уменьшите скорость отбора краном.';
  $('bEnd').hidden=!S.end;
  if(S.end)$('bEndT').textContent='Куб '+n(k.t,1)+' °C: перегон окончен. Выключите нагрев.';
  if(S.run!==lastRun){lastRun=S.run;buildCharts();loadHist();evSig='';loadEvents();}
}
function paintFix(c,d){
  const st=$('fxSt');st.textContent=S.fixStateText;st.className='pill '+S.fixState;
  $('fxCur').textContent=S.valid?n(c.t,2):'——';
  $('fxV').textContent=S.fix!=null?n(S.fix,2):'——';
  $('fxD').textContent=S.fix!=null&&S.valid?sgn(d,2):'——';
  $('fxWhen').textContent=S.fix!=null&&S.fixSrc?'последняя фиксация: '+(S.fixAt&&S.fixAt!=='—'?S.fixAt+', ':'')+S.fixSrc:'';
  $('fxFix').disabled=!!S.fixErr;$('fxFix').title=S.fixErr||'';
  $('fxOk').hidden=S.fixState!=='confirm';$('fxOk').disabled=!!S.fixErr;$('fxOk').title=S.fixErr||'';
  if(S.fixErr&&!$('fxMsg').textContent){$('fxMsg').className='msg bad';$('fxMsg').textContent='Нельзя зафиксировать: '+S.fixErr;}
  else if(!S.fixErr&&$('fxMsg').textContent.indexOf('Нельзя зафиксировать')===0)$('fxMsg').textContent='';
}
function buildCharts(){
  const list=S.run===3?[]:S.run===1?[['k','Куб','цветные зоны'],['c','Царга','синяя ниже '+n(S.col1,0)]]
    :[['c','Царга','Тфикс и пороги'],['k','Куб','цветные зоны'],['u','Узел отбора','']];
  $('charts').innerHTML=list.map(x=>'<div class="chart"><div class="hd"><h3>'+x[1]+' <span>'+x[2]+'</span></h3>'+
    '<span class="cur" id="cucv'+x[0]+'" hidden><b></b><button title="Убрать полоску">×</button></span></div><canvas id="cv'+x[0]+'"></canvas></div>').join('');
  CUR={};CH={};GEO={};
  list.forEach(x=>{const id='cv'+x[0],cv=$(id);let drag=false;
    // палец: ставим по касанию или ведём вбок; если палец повёл вверх-вниз, страница прокручивается, полоска не ставится
    cv.onpointerdown=e=>{drag=true;try{cv.setPointerCapture(e.pointerId);}catch(_){}if(e.pointerType!=='touch')curSet(id,e);};
    cv.onpointermove=e=>{if(drag)curSet(id,e);};
    cv.onpointerup=e=>{if(drag&&e.pointerType==='touch')curSet(id,e);drag=false;};
    cv.onpointercancel=()=>{drag=false;};
    $('cu'+id).querySelector('button').onclick=()=>{delete CUR[id];curRedraw(id);};});
}
// Полоска-курсор: у каждого графика своя. CUR[id] — момент в секундах работы контроллера (как H.now),
// поэтому после отпускания полоска стоит на этом моменте и съезжает влево вместе с графиком;
// часы — по часам телефона/компьютера: момент + (время браузера − H.now) в момент загрузки истории.
let CUR={},CH={},GEO={},hOff=0;
const clock=s=>{const d=new Date(s*1000);return [d.getHours(),d.getMinutes(),d.getSeconds()].map(v=>String(v).padStart(2,'0')).join(':');};
function curSet(id,e){
  const g=GEO[id];if(!g||!H)return;
  const x=e.clientX-$(id).getBoundingClientRect().left;
  const b=Math.max(0,Math.min(g.span,(g.x1-x)/(g.x1-g.x0)*g.span));
  CUR[id]=H.now-Math.round(b/H.step)*H.step;curRedraw(id);
}
function curRedraw(id){if(CH[id])chart(id,CH[id][0],CH[id][1]);else{const el=$('cu'+id);if(el)el.hidden=true;}}
function niceScale(vals,minSpan){
  let lo=Math.min(...vals),hi=Math.max(...vals);
  if(hi-lo<minSpan){const c=(lo+hi)/2;lo=c-minSpan/2;hi=c+minSpan/2;}
  const pad=(hi-lo)*0.08;lo-=pad;hi+=pad;
  const step=[0.01,0.02,0.05,0.1,0.2,0.5,1,2,5,10,20].find(s=>(hi-lo)/s<=6)||20;
  lo=Math.floor(lo/step+1e-9)*step;hi=Math.ceil(hi/step-1e-9)*step;
  const ticks=[];for(let v=lo;v<=hi+step/2;v+=step)ticks.push(Math.round(v*100)/100);
  return{lo,hi,ticks,dec:step<0.1?2:step<1?1:0};
}
function chart(id,vals,o){
  const cv=$(id);if(!cv)return;
  CH[id]=[vals,o];const cu=$('cu'+id);if(cu)cu.hidden=true;
  const dpr=window.devicePixelRatio||1,w=cv.clientWidth,h=cv.clientHeight;
  cv.width=w*dpr;cv.height=h*dpr;const g=cv.getContext('2d');g.scale(dpr,dpr);
  const x0=54,x1=w-10,y0=8,y1=h-24,N=vals.length,span=Math.max(1,(N-1)*H.step);
  g.font='12px system-ui,sans-serif';g.fillStyle=css('muted');
  const good=vals.filter(v=>v!=null);
  if(!good.length){g.textAlign='center';g.fillText('нет данных',w/2,h/2);return;}
  const sc=niceScale(good.concat(o.include||[]),o.minSpan);
  const X=b=>x1-(x1-x0)*b/span,Y=v=>y1-(y1-y0)*(Math.max(sc.lo,Math.min(sc.hi,v))-sc.lo)/(sc.hi-sc.lo);
  (o.bands||[]).forEach(b=>{const a=Math.max(b[0],sc.lo),z=Math.min(b[1],sc.hi);if(z<=a)return;
    g.globalAlpha=.14;g.fillStyle=css(b[2]);g.fillRect(x0,Y(z),x1-x0,Y(a)-Y(z));g.globalAlpha=1;});
  g.strokeStyle=css('line');g.lineWidth=1;g.fillStyle=css('muted');g.textAlign='right';
  sc.ticks.forEach(t=>{g.beginPath();g.moveTo(x0,Y(t)+.5);g.lineTo(x1,Y(t)+.5);g.stroke();g.fillText(n(t,sc.dec),x0-6,Y(t)+4);});
  if(o.fixes&&o.fixes.length){
    g.strokeStyle=css('ok');g.setLineDash([5,4]);g.lineWidth=1.25;
    o.fixes.forEach((f,i)=>{const nx=o.fixes[i+1];const a=Math.min(f[0],span),b=nx?nx[0]:0;if(b>span||f[1]==null)return;
      g.beginPath();g.moveTo(X(a),Y(f[1]));g.lineTo(X(b),Y(f[1]));g.stroke();});
    g.setLineDash([]);const f=o.fixes[o.fixes.length-1];g.fillStyle=css('ok');
    if(f[1]!=null)g.fillText('Тфикс '+n(f[1],2),x1-4,Y(f[1])-6);
  }
  g.strokeStyle=css('fg');g.lineWidth=1.6;g.beginPath();let pen=false;
  vals.forEach((v,i)=>{if(v==null){pen=false;return;}const x=X((N-1-i)*H.step),y=Y(v);if(pen)g.lineTo(x,y);else g.moveTo(x,y);pen=true;});
  g.stroke();
  const last=vals[N-1];if(last!=null){g.fillStyle=css('fg');g.beginPath();g.arc(x1,Y(last),3.5,0,7);g.fill();}
  g.fillStyle=css('muted');
  const lab=s=>s>=7200?Math.round(s/3600)+' ч':Math.round(s/60)+' мин';
  [[span,'start'],[span*2/3,'center'],[span/3,'center'],[0,'end']].forEach(([b,al])=>{g.textAlign=al;
    g.fillText(b?'−'+lab(b):'сейчас',X(b),h-6);});
  GEO[id]={x0,x1,span};
  const u=CUR[id];if(u==null)return;
  const k=Math.round((H.now-u)/H.step);
  if(k<0||k>N-1){delete CUR[id];return;}         // момент ушёл за левый край (или контроллер перезапускался)
  const xc=Math.round(X(k*H.step))+.5,v=vals[N-1-k];
  g.strokeStyle=css('cur');g.lineWidth=3;g.beginPath();g.moveTo(xc,y0-4);g.lineTo(xc,y1+4);g.stroke();
  if(cu){cu.querySelector('b').textContent=clock(u+hOff)+' · '+(v==null?'нет данных':n(v,id==='cvc'?2:1)+' °C');cu.hidden=false;}
}
function draw(){
  if(!H||!S||!S.run||S.run===3)return;
  const z=S.z,zb=[[-100,z[0],'cold'],[z[0],z[1],'ok'],[z[1],z[2],'warn'],[z[2],z[3],'hot'],[z[3],300,'bad']];
  chart('cvk',H.k,{minSpan:2,bands:zb});
  if(S.run===1){chart('cvc',H.c,{minSpan:2,bands:[[-100,S.col1,'cold'],[S.col1,300,'ok']]});return;}
  const f=S.fix,fx=H.fix||[];
  chart('cvc',H.c,{minSpan:0.12,include:f!=null?[f]:[],fixes:fx,
    bands:f!=null?[[-100,f+S.green,'ok'],[f+S.green,f+S.red,'warn'],[f+S.red,300,'bad']]:[]});
  chart('cvu',H.u,{minSpan:2,bands:[[-100,300,'ok']]});
}
</script></body></html>)HTML";

// =====================================================================
//  Настройки: http://kolonna.local/settings  (логин admin)
// =====================================================================
static const char PAGE_SETTINGS[] PROGMEM = R"HTML(<!doctype html>
<html lang="ru"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Настройки колонны</title>
<style>
[hidden]{display:none!important}
:root{--bg:#f3f4f1;--surface:#fff;--fg:#1b1f1d;--muted:#5d6762;--line:#d9ddd8;--accent:#2f6b55;--ok:#1e8a4c;--bad:#c83232}
@media(prefers-color-scheme:dark){:root{--bg:#121614;--surface:#1a1f1c;--fg:#e8ece9;--muted:#9aa49f;--line:#2c332f;--accent:#6fbf9c;--ok:#4fd18a;--bad:#ff6b6b;color-scheme:dark}}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--fg);font:15px/1.5 system-ui,-apple-system,"Segoe UI",Roboto,sans-serif}
.wrap{max-width:860px;margin:0 auto;padding:16px;display:grid;gap:14px}
header{display:flex;justify-content:space-between;align-items:center;gap:12px;flex-wrap:wrap}
h1{font-size:19px;margin:0}h2{font-size:16px;margin:0 0 8px}
a{color:var(--accent)}
section{background:var(--surface);border:1px solid var(--line);border-radius:10px;padding:14px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(170px,1fr));gap:10px 14px}
label{display:grid;gap:3px;font-size:13px;color:var(--muted)}
input,select{font:15px system-ui,sans-serif;padding:7px 9px;border:1px solid var(--line);border-radius:7px;background:var(--bg);color:var(--fg);width:100%}
input[type=checkbox]{width:auto}
.ch{border-top:1px solid var(--line);padding-top:10px;margin-top:10px}.ch:first-of-type{border:0;margin:0;padding:0}
.ch h3{font-size:14px;margin:0 0 6px;display:flex;gap:10px;align-items:center;flex-wrap:wrap}
.live{font:13px ui-monospace,Consolas,monospace;color:var(--muted)}
.note{font-size:13px;color:var(--muted);margin:8px 0 0}
button{font:600 15px system-ui,sans-serif;border:0;border-radius:8px;padding:10px 18px;background:var(--accent);color:#fff;cursor:pointer}
button.sec{background:var(--surface);color:var(--fg);border:1px solid var(--line);font-weight:500;padding:7px 12px}
.bar{position:sticky;bottom:0;background:var(--bg);padding:10px 0;display:flex;gap:12px;align-items:center;flex-wrap:wrap}
#msg{font-weight:600}
.nets{display:flex;flex-wrap:wrap;gap:6px;margin-top:8px}
.cal{display:flex;gap:8px;align-items:flex-start;flex-wrap:wrap;margin-top:8px}
.cb{display:grid;gap:5px}
.cbar{display:block;height:4px;border-radius:2px;background:var(--line);overflow:hidden}
.cbar i{display:block;height:100%;width:100%;background:var(--accent);transition:width .35s linear}
.calres{font-size:14px;margin:8px 0 0;display:flex;gap:8px 12px;align-items:center;flex-wrap:wrap}
.calres.bad{color:var(--bad)}.calres.ok{color:var(--ok)}
button:disabled{opacity:.6;cursor:default}
.lg{display:flex;align-items:center;gap:6px 12px;padding:6px 0;border-top:1px solid var(--line);font-size:14px;font-variant-numeric:tabular-nums}
.lg:first-child{border-top:0}.lg>span:first-child{flex:1;min-width:0}.lg .note{margin:0;flex:0 1 auto;text-align:right}.lg button{flex:none}
a.sec{display:inline-block;font:500 15px system-ui,sans-serif;border:1px solid var(--line);border-radius:8px;padding:7px 12px;background:var(--surface);color:var(--fg);text-decoration:none}
.imp{width:100%;border-collapse:collapse;font-size:14px;margin-top:8px}.imp th,.imp td{text-align:left;padding:5px 8px;border-top:1px solid var(--line);vertical-align:top}
.imp th{color:var(--muted);font-weight:500;border:0;font-size:13px}.imp td:first-child{white-space:nowrap}.imp td:nth-child(2){min-width:8em}.imp td.bad{color:var(--bad)}.imp td.same{color:var(--muted)}.imp td.new{color:var(--ok);font-weight:600}
</style></head><body><div class="wrap">
<header><h1>Настройки колонны</h1><a href="/">← Монитор</a></header>
<form id="f" style="display:grid;gap:14px">
<section><h2>Датчики</h2><div id="chs"></div>
<p class="note">PT1000 (основной) — резистор на модуле «432» (4300 Ом), PT100 (запасной) — «431» (430 Ом). Если пишет «проверьте тип и Rref»,
тип датчика или Rref не совпадают с модулем: при 20 °C PT1000 показывает около 1080 Ом, PT100 — около 108 Ом.
Выключенный канал не опрашивается, на экране у него «выключен».</p>
<p class="note"><b>Калибровка по льду.</b> Опустите датчик в стакан колотого льда с небольшим количеством воды и подождите 2–3 минуты.
Нажмите «Калибровать по льду» и не трогайте датчик, пока идёт полоска (10 с): прошивка усреднит сопротивление и предложит новый Rref,
при котором во льду будет ровно 0,00 °C. Если показывает дальше ±3 °C от нуля, датчик не во льду или в поле Rref не тот резистор:
тогда калибровка откажется. Откажется и тогда, когда показания плывут: датчик ещё не остыл во льду.
«Сбросить» возвращает Rref к номиналу (430 / 4300 Ом) и обнуляет поправку.
«Калибровать все три по льду» — то же сразу для всех включённых датчиков (все три в одном стакане со льдом), как кнопка
«Калибровка нуля» тестовой прошивки: «Сохранить годные» записывает те, у кого получилось, у остальных видна причина отказа.</p>
<div class="cal"><span class="cb"><button type="button" class="sec" id="calall">Калибровать все три по льду</button></span>
<span id="calallact" hidden><button type="button" id="csaveall">Сохранить годные</button> <button type="button" class="sec" id="ccanall">Отмена</button></span></div>
<p class="calres" id="calallmsg" hidden></p>
<p class="note"><b>Файл калибровки.</b> «Скачать калибровку» сохраняет в файл тип, Rref, поправку, провода и дату калибровки всех датчиков —
на случай перепрошивки, сброса настроек или замены контроллера. «Загрузить калибровку» показывает, что было и что станет, и записывает
только после «Записать» (Rref и поправку; тип и провода из файла не меняются). Калибровка относится к паре «датчик + модуль»:
если тип датчика или число проводов в файле не те, что стоят сейчас, этот датчик не загружается.</p>
<div class="cal"><a class="sec" href="/api/calib" download>Скачать калибровку</a><button type="button" class="sec" id="cload">Загрузить калибровку</button>
<input type="file" id="cfile" accept=".json,application/json" hidden></div>
<div id="cimp" hidden><table class="imp"><thead><tr><th>Датчик</th><th>Было</th><th>Станет</th></tr></thead><tbody id="cimpb"></tbody></table>
<div class="cal"><button type="button" id="cwrite">Записать</button><button type="button" class="sec" id="cimpcan">Отмена</button></div></div>
<p class="calres" id="cimpmsg" hidden></p></section>

<section><h2>Царга (второй перегон)</h2><div class="grid">
<label>Окно стабилизации, мин (2–15)<input name="win" type="number" min="2" max="15" step="1"></label>
<label>Зелёный до, +°C<input name="green" type="number" min="0.02" max="0.29" step="0.01"></label>
<label>Тревога выше, +°C<input name="red" type="number" min="0.03" max="0.30" step="0.01"></label>
<label>Задержка тревоги, с (1–10)<input name="delay" type="number" min="1" max="10" step="1"></label>
<label>Зуммер<select name="buzzer"><option value="1">включён</option><option value="0">выключен</option></select></label>
<label>Пар в узле отбора: датчик 3 выше, °C (30–90)<input name="steam" type="number" min="30" max="90" step="1"></label>
</div><p class="note">«Пар в узле отбора» — сигнал на разгоне второго перегона, когда датчик 3 впервые поднялся выше порога
(пар дошёл до узла отбора, пора приступать к стабилизации). Один раз за перегон.</p></section>

<section><h2>Клапан отбора (второй перегон)</h2><div class="grid">
<label>Тело: пауза, если царга выше Тфикс на, °C<input name="vDelta" type="number" min="0.02" max="0.30" step="0.01"></label>
<label>дольше, с (1–30)<input name="vDelay" type="number" min="1" max="30" step="1"></label>
<label>Пауза не короче, с (10–120)<input name="vWait" type="number" min="10" max="120" step="1"></label>
<label>Частые паузы: пауз (2–8)<input name="vN1" type="number" min="2" max="8" step="1"></label>
<label>за, мин (1–60)<input name="vMin1" type="number" min="1" max="60" step="1"></label>
<label>Куб от, °C (80–100)<input name="vCube" type="number" min="80" max="100" step="0.1"></label>
<label>тогда пауз (2–8)<input name="vN2" type="number" min="2" max="8" step="1"></label>
<label>за, мин (1–60)<input name="vMin2" type="number" min="1" max="60" step="1"></label>
<label>Хвосты: перегон окончен при кубе, °C (90–100)<input name="tailsEnd" type="number" min="90" max="100" step="0.1"></label>
</div><p class="note">Режим отбора выбирается на экране (нажатие на плитку «Узел отбора») или на главной странице.
На теле клапан закрывается на паузу, когда царга выше Тфикс на заданную величину дольше заданного времени,
и сразу — когда выше ещё на 0,01. Открывается, когда пауза длится не меньше заданного и царга ниже Тфикс;
если ещё не ниже — проверка снова через то же время. Частые паузы — сигнал и надпись «уменьшите скорость
отбора краном»; от заданной температуры куба действует вторая пара чисел.</p></section>

<section><h2>Куб</h2>
<div class="grid">
<label>2-й перегон: зелёный от<input name="z2_0" type="number" step="0.1"></label>
<label>жёлтый от<input name="z2_1" type="number" step="0.1"></label>
<label>оранжевый от<input name="z2_2" type="number" step="0.1"></label>
<label>красный от<input name="z2_3" type="number" step="0.1"></label>
<label>1-й перегон: зелёный от<input name="z1_0" type="number" step="0.5"></label>
<label>жёлтый от<input name="z1_1" type="number" step="0.5"></label>
<label>оранжевый от<input name="z1_2" type="number" step="0.5"></label>
<label>красный от<input name="z1_3" type="number" step="0.5"></label>
<label>1-й перегон: царга зелёная от<input name="col1" type="number" min="30" max="95" step="0.5"></label>
</div><p class="note">«Зелёный от» — это и порог сигнала «Включите охлаждение».</p></section>

<section><h2>Экран</h2><div class="grid">
<label>Подсветка, % (10–100)<input name="bright" type="number" min="10" max="100" step="5"></label>
<label>График куба, мин (1–30)<input name="chart" type="number" min="1" max="30" step="1"></label>
</div></section>

<section><h2>Wi-Fi</h2><p class="note" id="netnow" style="margin:0 0 8px"></p><div class="grid">
<label>Основная сеть<input name="ssid0" maxlength="32" autocomplete="off"></label>
<label>Пароль основной<input name="pass0" type="password" maxlength="64" autocomplete="new-password"></label>
<label>Запасная сеть<input name="ssid1" maxlength="32" autocomplete="off"></label>
<label>Пароль запасной<input name="pass1" type="password" maxlength="64" autocomplete="new-password"></label>
</div>
<p class="note">Пустое поле пароля — пароль не меняется. Чтобы стереть пароль (открытая сеть), введите «-».</p>
<div class="nets"><button type="button" class="sec" id="scan">Найти сети</button><span id="nets" class="nets"></span></div>
</section>

<section><h2>Пароль настроек</h2><div class="grid">
<label>Новый пароль (не короче 3 символов)<input name="webpass" type="password" maxlength="32" autocomplete="new-password"></label>
</div><p class="note">Логин всегда admin. Этот же пароль спрашивает Arduino IDE при прошивке по сети.</p></section>

<div class="bar"><button type="submit">Сохранить</button><span id="msg"></span></div>
</form>

<section><h2>Перегоны на контроллере</h2>
<p class="note" style="margin:0 0 8px" id="lognote">Скачать — на главной странице, блок «Прошлые перегоны».</p>
<div id="logs"></div><p class="note" id="logmsg"></p></section>

<section><h2>Обновление прошивки</h2>
<p class="note" style="margin:0 0 8px">Arduino IDE: Sketch → Export Compiled Binary, затем выберите файл kolonna.ino.bin.</p>
<input type="file" id="fw" accept=".bin"> <button type="button" id="up">Загрузить</button> <progress id="pr" max="100" value="0" hidden></progress> <span id="upmsg"></span>
</section>
</div>
<script>
const $=id=>document.getElementById(id),f=$('f');
const NAMES=['Датчик 1 — куб (CS GPIO4)','Датчик 2 — царга (CS GPIO5)','Датчик 3 — узел отбора / воздух (CS GPIO6)'];
const n=(v,d)=>v==null?'——':v.toFixed(d).replace('.',',');
function chRow(i){return '<div class="ch"><h3>'+NAMES[i]+' <label style="display:flex;gap:6px;align-items:center;color:var(--fg)"><input type="checkbox" name="c'+i+'on"> включён</label></h3>'+
'<div class="grid"><label>Тип<select name="c'+i+'type"><option value="100">PT100</option><option value="1000">PT1000</option></select></label>'+
'<label>Rref, Ом<input name="c'+i+'rref" type="number" step="0.01"></label>'+
'<label>Провода<select name="c'+i+'wires"><option>2</option><option>3</option><option>4</option></select></label>'+
'<label>Поправка, °C<input name="c'+i+'off" type="number" step="0.01" min="-10" max="10"></label></div>'+
'<p class="live" id="live'+i+'"></p>'+
'<div class="cal"><span class="cb"><button type="button" class="sec" id="cal'+i+'">Калибровать по льду</button><span class="cbar" id="cbar'+i+'" hidden><i id="cbari'+i+'"></i></span></span>'+
'<button type="button" class="sec" id="crst'+i+'">Сбросить</button></div>'+
'<div class="calres" id="cres'+i+'" hidden><span id="cmsg'+i+'"></span><span id="cact'+i+'" hidden><button type="button" id="csave'+i+'">Сохранить</button> <button type="button" class="sec" id="ccan'+i+'">Отмена</button></span></div></div>';}
$('chs').innerHTML=[0,1,2].map(chRow).join('');
for(let i=0;i<3;i++)f['c'+i+'type'].onchange=e=>{const r=f['c'+i+'rref'];const v=parseFloat(r.value);
  if(e.target.value==='1000'&&Math.abs(v-430)<15)r.value=4300;if(e.target.value==='100'&&Math.abs(v-4300)<150)r.value=430;};
let loaded=false;
async function load(){
  const r=await fetch('/api/settings',{cache:'no-store'});if(!r.ok)return;const s=await r.json();
  s.ch.forEach((c,i)=>{$('live'+i).textContent='сейчас: '+n(c.t,2)+' °C · '+n(c.ohm,2)+' Ом · '+c.txt+(c.fault?' · регистр ошибок 0x'+c.fault.toString(16):'')+(c.cal?' · калибровка по льду '+c.cal:'');
    if(loaded)return;f['c'+i+'on'].checked=c.on;f['c'+i+'type'].value=c.pt1000?'1000':'100';f['c'+i+'rref'].value=c.rref;f['c'+i+'wires'].value=c.wires;f['c'+i+'off'].value=c.off;});
  $('netnow').textContent='Сейчас: '+s.net+(s.ip?' · '+s.ip:'');
  if(loaded)return;loaded=true;
  ['win','green','red','delay','col1','chart','bright','steam','vDelta','vDelay','vWait','vN1','vMin1','vN2','vMin2','vCube','tailsEnd'].forEach(k=>f[k].value=s[k]);
  f.buzzer.value=s.buzzer?'1':'0';
  for(let i=0;i<4;i++){f['z2_'+i].value=s.z2[i];f['z1_'+i].value=s.z1[i];}
  for(let i=0;i<2;i++){f['ssid'+i].value=s.ssid[i];f['pass'+i].placeholder=s.passSet[i]?'•••••• (задан)':'не задан';}
}
load();setInterval(load,2000);
// ---- калибровка по льду
const calNote=['','',''],calSt=[0,0,0],calQuiet=[0,0,0];let calT=null,calLast=null,calGen=0,calAllMode=false;
const sg=v=>(v>0?'+':'')+n(v,2);
async function calGet(){try{const r=await fetch('/api/cal',{cache:'no-store'});return r.ok?await r.json():null;}catch(e){return null;}}
async function calPost(i,a){try{const r=await fetch('/api/cal',{method:'POST',body:new URLSearchParams({c:i,a:a})});
  if(r.status===401)return {ok:false,err:'нужен пароль настроек, обновите страницу'};return await r.json();}catch(e){return {ok:false,err:'нет связи'};}}
// опрос, пока идёт замер: не ответил — пробуем снова; ответ, начатый до нажатия кнопки, устарел — выбрасываем
function calPoll(ms){clearTimeout(calT);calT=setTimeout(async()=>{const g=calGen,j=await calGet();if(g!==calGen)return;if(j)calRender(j);else calPoll(1000);},ms);}
function calRender(j){if(!j||!j.ch)return;calLast=j;let run=false;
  j.ch.forEach((c,i)=>{const b=$('cal'+i),res=$('cres'+i),act=$('cact'+i);
    // результат или замер пропал не по кнопке — значит, настройки датчиков сохранили заново
    if(calSt[i]&&!c.st&&!calQuiet[i])calNote[i]={t:'Калибровка прервана: настройки датчиков сохранили заново (или её отменили в другой вкладке). Начните ещё раз.',bad:1};
    calSt[i]=c.st;
    run=run||c.st===1;b.disabled=c.st===1;b.textContent=c.st===1?'Измеряю…':'Калибровать по льду';
    $('cbar'+i).hidden=c.st!==1;if(c.st===1)$('cbari'+i).style.width=(Math.ceil(c.left/1000)/j.secs*100)+'%';
    if(c.st===2){res.hidden=false;act.hidden=false;
      if(c.err){res.className='calres bad';$('cmsg'+i).textContent=(c.t==null?'':'Датчик показал '+n(c.t+c.off,2)+' °C. ')+c.err+'. Rref не изменён.';$('csave'+i).hidden=true;$('ccan'+i).textContent='Понятно';}
      else{res.className='calres';$('cmsg'+i).textContent='Во льду '+n(c.t+c.off,2)+' °C ('+n(c.ohm,2)+' Ом). Rref '+n(c.rref,2)+' → '+n(c.nrref,2)+' Ом'+(c.off?', поправка '+sg(c.off)+' → 0':'')+'. После «Сохранить» во льду будет 0,00 °C.';$('csave'+i).hidden=false;$('ccan'+i).textContent='Отмена';}
    }else{act.hidden=true;res.hidden=!calNote[i];
      if(calNote[i]){res.className=calNote[i].bad?'calres bad':'calres ok';$('cmsg'+i).textContent=calNote[i].t;}else $('cmsg'+i).textContent='';}});
  const done=j.ch.filter(c=>c.st===2).length,good=j.ch.filter(c=>c.st===2&&!c.err).length;
  $('calall').disabled=run;$('calall').textContent=run&&calAllMode?'Измеряю все…':'Калибровать все три по льду';
  if(!done&&!run)calAllMode=false;
  $('calallact').hidden=!(calAllMode&&!run&&done);$('csaveall').hidden=!good;$('csaveall').textContent='Сохранить годные ('+good+')';
  if(run)calPoll(500);else clearTimeout(calT);}
function calApplied(i,j,t){if(!j.ok){calNote[i]={t:'Не получилось: '+(j.err||'нет связи'),bad:1};return;}
  const c=j.ch[i];f['c'+i+'rref'].value=c.rref;f['c'+i+'off'].value=0;calNote[i]={t:t+': Rref '+n(c.rref,2)+' Ом, поправка 0.'};}
// кнопка калибровки: пока ждём ответ, опрос молчит, а пропажа результата этого датчика — не «прервана»
async function calAct(i,a,btns,done){btns.forEach(b=>b.disabled=true);calQuiet[i]++;clearTimeout(calT);calGen++;
  const j=await calPost(i,a);calGen++;btns.forEach(b=>b.disabled=false);
  done(j);calRender(j.ch?j:calLast);calQuiet[i]--;}
for(let i=0;i<3;i++){
  $('cal'+i).onclick=()=>{calNote[i]='';calAct(i,'start',[$('cal'+i)],j=>{if(!j.ok)calNote[i]={t:'Не начал: '+(j.err||'нет связи'),bad:1};});};
  $('csave'+i).onclick=()=>calAct(i,'save',[$('csave'+i),$('ccan'+i)],j=>calApplied(i,j,'Сохранено'));
  $('ccan'+i).onclick=()=>calAct(i,'cancel',[$('csave'+i),$('ccan'+i)],j=>{calNote[i]=j.ok?'':{t:'Не получилось: '+(j.err||'нет связи'),bad:1};});
  let armed=0;const rb=$('crst'+i);
  rb.onclick=async()=>{if(!armed){const nom=calLast?n(calLast.ch[i].nom,0):'номинал';rb.textContent='Точно сбросить к '+nom+' Ом?';
      armed=setTimeout(()=>{armed=0;rb.textContent='Сбросить';},4000);return;}
    clearTimeout(armed);armed=0;rb.textContent='Сбросить';calAct(i,'reset',[rb],j=>calApplied(i,j,'Сброшено к номиналу'));};
}
// все три сразу: у каждого датчика своя полоска и свой результат, общие кнопки — «Сохранить годные» и «Отмена»
const allMsg=(t,bad)=>{const m=$('calallmsg');m.hidden=!t;m.textContent=t;m.className=bad?'calres bad':'calres ok';};
async function calAll(a,btns,done){btns.forEach(b=>b.disabled=true);[0,1,2].forEach(i=>calQuiet[i]++);clearTimeout(calT);calGen++;
  const before=calLast,j=await calPost('all',a);calGen++;btns.forEach(b=>b.disabled=false);
  done(j,before);calRender(j.ch?j:calLast);[0,1,2].forEach(i=>calQuiet[i]--);}
$('calall').onclick=()=>{allMsg('');[0,1,2].forEach(i=>calNote[i]='');calAllMode=true;
  calAll('start',[$('calall')],j=>{if(!j.ok){calAllMode=false;allMsg('Не начал: '+(j.err||'нет связи'),1);}});};
$('csaveall').onclick=()=>calAll('save',[$('csaveall'),$('ccanall')],(j,before)=>{
  if(!j.ok){allMsg('Не получилось: '+(j.err||'нет связи'),1);return;}
  let k=0;j.ch.forEach((c,i)=>{const b=before&&before.ch[i];if(b&&b.st===2&&!b.err&&c.st===0){k++;f['c'+i+'rref'].value=c.rref;f['c'+i+'off'].value=0;calNote[i]={t:'Сохранено: Rref '+n(c.rref,2)+' Ом, поправка 0.'};}});
  calAllMode=false;allMsg('Сохранено датчиков: '+k+'. Во льду они теперь показывают 0,00 °C.');});
$('ccanall').onclick=()=>calAll('cancel',[$('csaveall'),$('ccanall')],j=>{calAllMode=false;allMsg(j.ok?'':'Не получилось: '+(j.err||'нет связи'),!j.ok);});
calPoll(0);
// ---- файл калибровки: скачать — ссылка /api/calib; загрузить — файл идёт на проверку, таблица «было → станет», потом «Записать»
const CHN=['куб','царга','узел отбора'];let calibText='';
const cmsg=(t,bad)=>{const m=$('cimpmsg');m.hidden=!t;m.textContent=t;m.className=bad?'calres bad':'calres';};
// причина отказа повторяет текст из файла — в таблицу только как текст, не как разметка
const esc=s=>String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
function calibShow(j){
  $('cimpb').innerHTML=j.ch.map(c=>'<tr><td>Датчик '+c.n+'<br>'+CHN[c.n-1]+'</td><td>'+(c.was.pt1000?'PT1000':'PT100')+' · '+c.was.wires+' пр.<br>'+n(c.was.rref,2)+' Ом · '+sg(c.was.off)+' °C'+(c.was.cal?'<br>'+c.was.cal:'')+'</td>'+
    (c.ok?(c.same?'<td class="same">без изменений</td>':'<td class="new">'+n(c.new.rref,2)+' Ом · '+sg(c.new.off)+' °C'+(c.new.cal?'<br>'+c.new.cal:'')+'</td>')
      :'<td class="bad">не загружается: '+esc(c.why)+'</td>')+'</tr>').join('');
  $('cimp').hidden=false;$('cwrite').hidden=!j.ch.some(c=>c.ok&&!c.same);}
async function calibPost(a){try{const r=await fetch('/api/calib',{method:'POST',body:new URLSearchParams({a:a,j:calibText})});
  if(r.status===401)return {ok:false,err:'нужен пароль настроек, обновите страницу'};return await r.json();}catch(e){return {ok:false,err:'нет связи'};}}
$('cload').onclick=()=>$('cfile').click();
$('cfile').onchange=async()=>{const file=$('cfile').files[0];if(!file)return;calibText=await file.text();$('cfile').value='';
  const j=await calibPost('check');if(!j.ok){$('cimp').hidden=true;cmsg('Файл не подходит: '+j.err,1);return;}
  cmsg('Файл '+file.name+': проверьте таблицу и нажмите «Записать»');calibShow(j);};
$('cimpcan').onclick=()=>{$('cimp').hidden=true;cmsg('');};
$('cwrite').onclick=async()=>{$('cwrite').disabled=true;const j=await calibPost('write');$('cwrite').disabled=false;
  if(!j.ok){cmsg('Не записано: '+j.err,1);return;}
  $('cimp').hidden=true;cmsg(j.written?'Записано (датчиков: '+j.written+'). Rref и поправки уже работают':'Записывать нечего: всё уже так и стоит');
  loaded=false;load();calPoll(700);};
f.onsubmit=async e=>{e.preventDefault();const p=new URLSearchParams();
  for(const el of f.elements){if(!el.name)continue;p.append(el.name,el.type==='checkbox'?(el.checked?'1':'0'):el.value);}
  $('msg').textContent='Сохраняю…';
  try{const r=await fetch('/api/settings',{method:'POST',body:p});const j=await r.json();
    $('msg').textContent=j.relogin?'Сохранено. Пароль изменён — браузер спросит новый.':'Сохранено, уже работает';
    $('msg').style.color='var(--ok)';f.pass0.value=f.pass1.value=f.webpass.value='';loaded=false;load();
    calPoll(700);}
  catch(e){$('msg').textContent='Не сохранилось: нет связи';$('msg').style.color='var(--bad)';}};
$('scan').onclick=async()=>{$('nets').textContent='ищу…';
  for(let k=0;k<20;k++){const j=await(await fetch('/api/scan')).json();
    if(j.list){$('nets').innerHTML='';[...new Map(j.list.map(x=>[x.ssid,x])).values()].filter(x=>x.ssid).forEach(x=>{
      const b=document.createElement('button');b.type='button';b.className='sec';b.textContent=x.ssid+' ('+x.rssi+' дБм)';
      b.onclick=()=>{const t=f.ssid0.value?'1':'0';f['ssid'+t].value=x.ssid;f['pass'+t].focus();};$('nets').appendChild(b);});return;}
    await new Promise(r=>setTimeout(r,700));}
  $('nets').textContent='не удалось';};
// ---- прошлые перегоны: удалить (текущий и последний нельзя — их продолжит «Продолжить»)
const dur=m=>m>=60?Math.floor(m/60)+' ч '+(m%60)+' мин':m+' мин';
const lname=x=>(x.run===1?'Первый':'Второй')+' перегон №'+x.n+' от '+(x.start?x.start.slice(0,10)+' '+x.start.slice(11,16):'(дата неизвестна)');
async function loadLogs(){
  let j;try{j=await(await fetch('/api/logs',{cache:'no-store'})).json();}catch(e){return;}
  $('lognote').textContent='Хранятся последние '+j.keep+' перегонов, старые удаляются сами при старте нового. Скачать — на главной странице, блок «Прошлые перегоны».';
  $('logs').innerHTML=!j.fs?'<p class="note">Память для логов не работает</p>':j.logs.length?j.logs.map(x=>'<div class="lg"><span><b>'+lname(x)+'</b> · '+dur(x.min)+' · '+Math.max(1,Math.round(x.size/1024))+' КБ</span>'+
    (x.del?'<button type="button" class="sec" data-n="'+x.n+'" data-d="'+(x.start?x.start.slice(0,10):'')+'" data-r="'+(x.run===1?'первый':'второй')+'">Удалить</button>'
      :'<span class="note">'+(x.cur?(x.live?'идёт':'текущий'):'последний: его можно продолжить')+', удалить нельзя</span>')+'</div>').join('')
    :'<p class="note">Перегонов на контроллере пока нет</p>';
  $('logs').querySelectorAll('button[data-n]').forEach(b=>b.onclick=async()=>{
    if(!confirm('Удалить '+b.dataset.r+' перегон №'+b.dataset.n+(b.dataset.d?' от '+b.dataset.d:'')+'?'))return;
    b.disabled=true;let t;
    try{const r=await fetch('/api/logdel?n='+b.dataset.n,{method:'POST'});const k=await r.json();t=k.ok?'Перегон №'+b.dataset.n+' удалён':'Не удалён: '+k.msg;}
    catch(e){t='Не удалён: нет связи';}
    $('logmsg').textContent=t;loadLogs();});
}
loadLogs();
$('up').onclick=()=>{const file=$('fw').files[0];if(!file){$('upmsg').textContent='выберите файл .bin';return;}
  const fd=new FormData();fd.append('fw',file,file.name);const x=new XMLHttpRequest();
  $('pr').hidden=false;x.upload.onprogress=e=>{if(e.lengthComputable)$('pr').value=e.loaded/e.total*100;};
  x.onload=()=>{$('upmsg').textContent=x.responseText;};x.onerror=()=>{$('upmsg').textContent='ошибка связи';};
  x.open('POST','/update');x.send(fd);};
</script></body></html>)HTML";
