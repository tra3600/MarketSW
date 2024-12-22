#include <iostream>
#include <vector>
#include <string>
#include "smtp_client.h"
#include "database.h"

// Structure pour stocker les informations des clients
struct Client {
    std::string name;
    std::string email;
    bool subscribed;
};

// Structure pour stocker les informations des campagnes
struct Campaign {
    std::string subject;
    std::string body;
    std::vector<Client> recipients;
};

// Fonction pour créer une nouvelle campagne
Campaign createCampaign() {
    Campaign campaign;
    std::cout << "Enter campaign subject: ";
    std::getline(std::cin, campaign.subject);
    std::cout << "Enter campaign body: ";
    std::getline(std::cin, campaign.body);
    return campaign;
}

// Fonction pour envoyer une campagne par email
void sendCampaign(const Campaign& campaign) {
    SmtpClient smtpClient("smtp.example.com", 587, "username", "password");

    for (const auto& client : campaign.recipients) {
        if (client.subscribed) {
            smtpClient.sendEmail(client.email, campaign.subject, campaign.body);
            std::cout << "Email sent to " << client.email << std::endl;
        }
    }
}

// Fonction pour gérer les abonnements des clients
void manageSubscriptions(std::vector<Client>& clients) {
    for (auto& client : clients) {
        std::string response;
        std::cout << "Client: " << client.name << " (" << client.email << ")\n";
        std::cout << "Subscribe to newsletter? (yes/no): ";
        std::getline(std::cin, response);
        client.subscribed = (response == "yes");
    }
}

int main() {
    std::vector<Client> clients = {
        {"Alice", "alice@example.com", false},
        {"Bob", "bob@example.com", false},
        // Ajoutez plus de clients ici
    };

    std::cout << "Welcome to the Marketing Software for SMEs!" << std::endl;

    while (true) {
        int choice;
        std::cout << "1. Create Campaign\n2. Send Campaign\n3. Manage Subscriptions\n4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignorer le caractère de nouvelle ligne

        switch (choice) {
            case 1: {
                Campaign campaign = createCampaign();
                campaign.recipients = clients;
                sendCampaign(campaign);
                break;
            }
            case 2: {
                // Simuler l'envoi d'une campagne existante
                if (!clients.empty()) {
                    Campaign campaign = createCampaign();
                    campaign.recipients = clients;
                    sendCampaign(campaign);
                } else {
                    std::cout << "No clients available for sending campaigns." << std::endl;
                }
                break;
            }
            case 3:
                manageSubscriptions(clients);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}