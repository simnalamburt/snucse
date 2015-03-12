Web Based Real-time Electricity Monitoring Service
========
2013-11392 Hyeon Kim

Problem
--------
Even though the effort of government's power saving campaign, citizens hardly
know what actually reduces their power usage. People receive their power bills
only once a week and most people rarely checks their power meter because of its
bad position and UX. In short, people receives their feedback of power usage too
late.

As a solution of this problem, I suggest to make in-home real-time power usage
webservice using Encored Technologies' Energy Planner device.

Hardware
--------
Energy Planner made by Encored Technologies is easy to install for most houses,
and it provides real-time and accumulated power usage to users via HTTP
protocol. Also it provides informations about 'Standby power' which most power
meters aren't able to measure.

Solution
--------
We can easily develop a web service which provides real-time power usage
information to user using RESTful API of Encored's Energy Planner. Giving real
time power usage feedback instead of monthly power bill to users will let the
users to learn what makes high power usage and what doesn't. Ultimately, this
solution will achieve *voluntary* power saving.

Analyzing the daily power usage pattern, it can send users a warning if it
detects abnormal power usage. For example, if a door of refrigerator is opened
while the user is sleeping, we can give a feed back of it to user.

Using the accumulated monthly power usage info, we can give a user feedback
about which level the user is in of progressive tax. Most people know that the
power tax of Korea is progressive tax but almost no people checks their level of
progressive tax each month. We can visualize it, warn or stop user preventing so
called 'tax bomb'.

Also we can draw a trendline of power usage graph and forecast their power tax
to users. Perhaps this way could be more effective than letting users to know
their lever of progressive power tex.

Implementation
--------
This service will be a web service, but it'll be developed in mobile-first.
Because the gist of this project is giving an ease monitoring tool to users.

Volatile informations like real-time power usage informations will be stored in
Redis, in-memory key-value store. And long-term data like monthly power usage
information will be stored in PostgreSQL. Server side applications will be built
on top of Ruby on Rails and client side will be developed with AngularJS.

Effect
--------
As I said this solution will achieve people's voluntary power saving. Instead of
repeating slogans to people, this solution will let people to save their power
willingly. Furthermore, this solution will be a good example of how to gamify
existing campaigns, and show a new way to change the world better place.
