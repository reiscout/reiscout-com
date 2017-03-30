Feature: Check Contact US block on homepage.
  Scenario: Fill in the block.
    Given I am in the "/" path
    And I fill in "Full Name:" with "John Doe"
    And I fill in "Email:" with "johnny.doe@sample.com"
    And I fill in "Message:" with "test message"
    And I press "Send message"
    Then I should see "Message successfully sent"
    And I should not see "SMTP ->"