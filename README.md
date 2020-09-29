# The Cash Flow Manager App is currently under construction! 
Check back frequently for updates.
- - - -

Cash Flow Manager
=========

The Cash Flow Manager desktop app is a complete personal expense, income, and investment manager built with C++14 in Qt. The app also provides mortgage, asset, and net worth tracking and analysis.


Table of contents
=================

<!--ts-->
   * [Cash Flow Manager](#cash-flow-manager)
   * [Table of contents](#table-of-contents)
   * [Installation](#installation)
   * [Usage](#usage)
      * [Budget Dashboard](#budget-dashboard)
      * [Monthly Budget Summary View](#monthly-budget-summary-view)
	  * [Monthly Expense Type Summary View](#monthly-expense-type-summary-view)
	  * [Yearly Budget Summary View](#yearly-budget-summary-view)
	  * [Yearly Income Summary View](#yearly-income-summary-view)
	  * [Automatic Monthly Payments Summary View](#automatic-monthly-payments-summary-view)
	  * [Mortgage Summary View](#mortgage-summary-view)
	  * [Asset and Net Worth Summary View](#asset-and-net-worth-summary-view)
	  * [Add Expense Transaction](#add-expense-transaction)
	  * [Add Expense Types](#add-expense-types)
	  * [Update Expense Types](#update-expense-types)
	  * [Add Investment Transaction](#add-investment-transaction)
	  * [Add Investment Types](#add-investment-types)
	  * [Update Investment Types](#update-investment-types)
	  * [Add Income Transaction](#add-income-transaction)
	  * [Update Automatic Monthly Payments](#update-automatic-monthly-payments)
	  * [Update Mortgage Information](#update-mortgage-information)
<!--te-->


Installation
============

Installation instructions coming soon!


Usage
=====


Budget Dashboard
-----

The Budget Dashboard provides an all-inclusive, simplified look at your financial health via two tabs in the main window: Monthly and Yearly Breakdown. 

<p align="center">
  <img src="/screenshots/Budget_Dashboard_Monthly_Breakdown.jpg" width="650" height="523"/><br>
  <i>Figure 1 - Budget Dashboard Monthly Breakdown Tab View</i>
</p>

The most despised yet critical aspect of personal finance is creating and tracking your month-to-month budget. After creating expense types and their associated monthly budget amounts, the Budget Dashboard updates automatically as transactions are added to show if you are on track. The *Expense Budget Status* bar chart is the best indicator of your spending habits for the month. Don't let the entire bar fill with red. Aim to keep as much of it green as possible by spending less than you make for the month and staying under-budget. The *Expense Budget* table gives you an in-depth categorized analysis of specifically where your hard earned dollars are going.

Similar to spending habits, you should also establish and track monthly investment targets. These types of investments are intended to be funded from net income. This includes brokerage accounts and Traditional or Roth IRAs but not investments funded via employer-withheld salary contributions, such as a 401k account. But don't worry if you aren't ready to invest in anything yet. The Cash Flow Manager app will not show the status of investments unless you add them.

<p align="center">
  <img src="/screenshots/Budget_Dashboard_Yearly_Breakdown.jpg" width="650" height="523"/><br>
  <i>Figure 2 - Budget Dashboard Yearly Breakdown Tab View</i>
</p>

Both the monthly and yearly *Breakdown* tables give you a holistic view of your financial situation. It shows the following information:

* Expenses
* Investments
* Income
* Cash saved
* Budget surplus
* Savings ratio
* Additional principal paid, if a mortgage is configured 

The savings ratio is simply yearly expenses divided by yearly income multiplied by 100 to get a percentage. Budget surplus is the amount remaining in the budget for the month. The cash saved amount is the result of subtracting expenses and investments from income, which should be positive. A negative cash saved value is undesirable because it signifies that you are investing too much, spending too much, or both.

The *Income Distribution* pie chart within the Yearly Breakdown tab displays a different type of visualization of where your money is going. Just like with the *Expense Budget Status* bar chart, keep the red expense section as small as possible by spending less.
<br>


Monthly Budget Summary View
-----------

The Monthly Budget Summary View shows categorized expenses and investments for each month of the current year. This dialog is beneficial because it allows you to see which expense categories 
were over-budget, or under-budget, throughout the year so that spending can be adjusted accordingly. Additionally, it shows investment amounts in relation to their defined targets. Any category amount that is over-budget or less than the investment target, is shaded in red. 
For each month, the view displays the final cash saved. As discussed previously, this value is what remains after subtracting expenses and investments from income for the month.

<p align="center">
  <img src="/screenshots/Monthly_Budget_Summary.jpg" width="750" height="571"/><br>
  <i>Figure 3 - Monthly Budget Summary View</i>
</p>
<br>


Monthly Expense Type Summary View
-----------

The capability to view the individual transactions for an expense category is a key feature. When an expense category runs over-budget for a particular month, it is beneficial to see which transaction(s) 
contributed to the increased spending. When launching the Monthly Expense Type Summary View, a prompt will ask you which expense type to display. After selecting the category, all of the 
associated transactions will be displayed in a table for each month of the year. Some types may have none or just a single transaction per month, such as utility expenses. Others will have a 
variable number of transactions, such as food or miscellaneous expenses. Each monthly table displays the amount spent and also the remaining budget as transactions are added.

<p align="center">
  <img src="/screenshots/Monthly_Expense_Type_Summary.jpg" width="750" height="571"/><br>
  <i>Figure 4 - Monthly Expense Type Summary View for Food Expenses</i>
</p>
<br>


Yearly Budget Summary View
-----------

For a more granular perspective into how your yearly income is being distributed to expenses and investments, the Yearly Budget Summary View shows the dollar amounts spent or invested by category.
The two tables that show expenses and investments are sortable by amount, relative percentage, or name.

<p align="center">
  <img src="/screenshots/Yearly_Budget_Summary.jpg" width="500" height="469"/><br>
  <i>Figure 5 - Yearly Budget Summary View</i>
</p>
<br>


Yearly Income Summary View
-----------

For most individuals, cash inflow is obtained through salary or supplemental income, such as investment income or dividends that aren't reinvested, rental income, credit card cash-back rewards, 
expense reimbursements, or payments from friends and family. The salary table allows you to track steady income and overtime, if applicable, from a job while the supplemental income table shows all miscellaneous 
income sources throughout the year.

<p align="center">
  <img src="/screenshots/Yearly_Income_Summary.jpg" width="500" height="469"/><br>
  <i>Figure 6 - Yearly Income Summary View</i>
</p>
<br>


Automatic Monthly Payments Summary View
-----------

Many types of bills or expenses can be paid automatically via ACH transfer, such utilities, wireless charges, mortgages, and investment contributions. Although this adds convenience, it can be difficult to remember exactly 
how much is scheduled to be drafted from your bank accounts. The Automatic Monthly Payments Summary View displays all of the fixed expense monthly payments along with the account 
from which each one is paid.

<p align="center">
  <img src="/screenshots/Automatic_Monthly_Payments_Summary.jpg" width="500" height="300"/><br>
  <i>Figure 7 - Automatic Monthly Payments Summary View</i>
</p>
<br>


Mortgage Summary View
-----------

If you bought a home, condo, or apartment to serve as your primary residence, you probably have a mortgage loan. Understanding how a mortgage works can be a difficult task but the Mortgage 
Summary View breaks down all the important information into a simple table. First, the parameters for the mortgage, such as the total loan amount, yearly interest rate, term, and 
date of the first payment must be configured. The [Update Mortgage Information](#update-mortgage-information) section provides more details on this. The table then automatically calculates the base monthly payment, which <b>does not</b> include taxes, insurance, or fees, and displays 
a payment schedule for the life of the mortgage. It is assumed that the mortgage follows a traditional monthly payment requirement. Each row shows the exact dollar amount for principal and interest, 
as well as any additional principal. As more payments are made, the remaining loan balance will decrease 
as the principal amount increases. Mortgage payments, including additional principal payments, are added as normal expense transactions. See the [Add Expense Transaction](#add-expense-transaction) section 
for more information. Rows within the table are shaded yellow to indicate payments that were made for the associated month. If the mortgage terms were to change at any point, 
such as for a refinance, all information in the view will be re-calculated automatically.

<p align="center">
  <img src="/screenshots/Mortgage_Summary.jpg" width="700" height="651"/><br>
  <i>Figure 8 - Mortgage Summary View</i>
</p>
<br>


Asset and Net Worth Summary View
-----------

There is no better indicator of your financial wellbeing than net worth. Personal net worth is the cumulative total of assets minus liabilities. Cash, bank accounts, investment accounts, property equity, 
business equity, annuities, bonds, vehicles, and certificates of deposit are all examples of assets. Liabilities include student loans, credit card debt, personal loans, and unpaid medical bills. To calculate 
equity for vehicles, property, or any other asset that was financed, it is important to subtract the remaining loan amount from the market value. Assets that can be immediately 
converted to cash are considered to be liquid while those that can't are illiquid. Illiquid assets are most retirement investment accounts, property, and vehicles. The Asset and Net Worth Summary View 
tracks the growth or decline of net worth and asset values over time. The asset table shows the dollar amount of assets throughout the year and the percentage of change month-to-month. The net worth tracking 
graph displays a visualization of total net worth progression, which is equal to liquid plus illiquid asset values, over the past 12 months.

<p align="center">
  <img src="/screenshots/Asset_And_Net_Worth_Summary.jpg" width="900" height="487"/><br>
  <i>Figure 9 - Asset and Net Worth Summary View</i>
</p>
<br>


Add Expense Transaction
-----------

To add an expense transaction, simply use the dropbox to select the applicable expense type, add an optional description, set the transaction date, and set the dollar amount. If the expense 
type is a mortgage, an edit box for additional principal will appear. The additional principal payment will be $0.00 by default.

<p align="center">
  <img src="/screenshots/Add_Expense_Transaction.jpg" width="450" height="236"/><br>
  <i>Figure 10 - Add Expense Transaction Window</i>
</p>
<br>


Add Expense Types
-----------

Before any transactions can be added, you must create expense types. A fixed expense type has a cost that does not change from month to month. In this case, the budget amount will exactly 
match the amount paid each month. Variable expense types are those that have an unknown total cost for the month. The budget amount for these types is the maximum amount that you can spend 
for related items or services. Fixed cost expenses include fixed-rate loan payments, certain utility bills, and insurance payments. Examples of variable expense types are food, miscellaneous, 
and gas. An expense type is considered a "required monthly expense" if payment must be made at least once per month. This includes mortgage or loan payments and most utility bills. Types that 
are not required monthly expenses are food, miscellaneous, and gas. Setting which expense types are required allows the Cash Flow Manager to show if bills are unpaid for the current or previous 
months in the Monthly Budget Summary View. When choosing a budget for the new expense type, set a realistic amount that challenges you to be conscious of spending but not too restrictive. The 
budget can always be adjusted at any time. 

<p align="center">
  <img src="/screenshots/Add_Expense_Type.jpg" width="450" height="209"/><br>
  <i>Figure 11 - Add Expense Type Window</i>
</p>
<br>


Update Expense Types
-----------

Expense types and their associated budgets will rarely stay the same over time. The Update/Delete Expense Type Window allows you to make changes to or delete any existing expense type. This is 
most useful for quickly adjusting monthly budgets.

<p align="center">
  <img src="/screenshots/Update_Expense_Type.jpg" width="450" height="231"/><br>
  <i>Figure 12 - Update/Delete Expense Type Window</i>
</p>
<br>


Add Investment Transaction
-----------

Adding an investment transaction is simple. Just select the investment type from the dropdown box, set the transaction date, and enter the dollar amount. Again, these types of investments are 
intended to be funded through net income, not from pre-tax, roth, or after-tax employer-withholdings.

<p align="center">
  <img src="/screenshots/Add_Investment_Transaction.jpg" width="450" height="180"/><br>
  <i>Figure 13 - Add Investment Transaction Window</i>
</p>
<br>


Add Investment Types
-----------

To add an investment type, choose a unique name and a target amount that you wish to invest each month. If you want to track an investment but do not want to create a monthly goal, 
you can just set the target to $0.00.

<p align="center">
  <img src="/screenshots/Add_Investment_Type.jpg" width="450" height="181"/><br>
  <i>Figure 14 - Add Investment Type Window</i>
</p>
<br>


Update Investment Types
-----------

Just as existing expense types can be updated or deleted, the same can be done with investment types.

<p align="center">
  <img src="/screenshots/Update_Investment_Type.jpg" width="450" height="181"/><br>
  <i>Figure 15 - Update/Delete Investment Type Window</i>
</p>
<br>


Add Income Transaction
-----------

Any net cash inflow from salary or supplemental sources is considered an income transaction. When entering a salary income transaction, enter any overtime hours, if applicable. For 
supplemental income, add a description to document the source of the cash. For example, a supplemental income description may be "2020 Federal Income Tax Return".

<p align="center">
  <img src="/screenshots/Add_Income_Transaction.jpg" width="450" height="224"/><br>
  <i>Figure 16 - Add Income Transaction Window</i>
</p>
<br>


Update Automatic Monthly Payments
-----------

Adding, deleting, and updating automatic monthly payment information can be performed within the same window. If the "Add Payment" radio button 
is selected, enter the bank account name from which the payment will be drafted each month, a description, and the amount. When the "Update 
or Delete Payment" radio button is selected, click an existing row entry for a monthly payment within the table to update or 
delete it.

<p align="center">
  <img src="/screenshots/Add_Update_Automatic_Monthly_Payments.jpg" width="500" height="400"/><br>
  <i>Figure 17 - Add/Update Automatic Monthly Payment Window</i>
</p>
<br>


Update Mortgage Information
-----------

To initially setup or update the mortgage information, enter the total loan amount, a conservative estimate for the current market value of 
the property, the yearly interest rate, the loan term in years, and the date that the first payment was due. The total loan amount is 
the original dollar amount that was borrowed, not the remaining loan balance. The market value is used to calculate asset value and net worth and 
should be updated periodically as the property value rises or falls over time. Given this information, the monthly base payment for the mortgage will be 
calculated automatically.

<p align="center">
  <img src="/screenshots/Update_Mortgage_Information.jpg" width="450" height="279"/><br>
  <i>Figure 18 - Update Mortgage Information Window</i>
</p>
<br>

