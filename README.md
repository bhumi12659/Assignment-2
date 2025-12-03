# Assignment-2
modifications compared to the old version:

1. High Score System Added

Loads highscore.txt on startup

Updates and saves new high score automatically


2. Multiple Sound Effects

Movement sound

Scoring sound

Crash sound

Speed-up sound
(Old game had only basic or single audio behavior)


3. Difficulty Increase

Speed reduces gradually as score increases

Game gets harder the longer you survive


4. Cleaner Input Handling

Proper arrow-key detection

Added quit key ('Q')

Fixed input buffer issues


5. Cleaner Layout & UI

Better console formatting

Visible score + high score

Structured lane borders for readability


6. Game Loop Separated Into a Function

playGame() handles the gameplay

main() handles menu, replay logic, and scores

Cleaner and easier to maintain


7. Better Obstacle + Player Rendering

Consistent ASCII UI

Uses loops instead of repeated prints


✅ 8. Removed Flickering Removed using Clear Screen

Uses system("cls") frame updates
